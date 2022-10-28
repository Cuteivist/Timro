#include "TimeController.h"

#include <QDateTime>
#include <QDebug>

#include "sql/SqlWorker.h"

#define SAVE_INTERVAL_SEC 30

using namespace Qt::Literals::StringLiterals;

TimeController::TimeController(QObject *parent)
    : QObject{parent}
{
    mWorkTimer.setTimerType(Qt::PreciseTimer);
    mWorkTimer.setInterval(1000);
    connect(&mWorkTimer, &QTimer::timeout, this, &TimeController::onWorkTimerTimeout);

    mBreakTimer.setTimerType(Qt::PreciseTimer);
    mBreakTimer.setInterval(1000);
    connect(&mBreakTimer, &QTimer::timeout, this, &TimeController::onBreakTimerTimeout);

    connect(this, &TimeController::requestSaveWorklog, this, &TimeController::onRequestSaveWorklog);
}

void TimeController::init()
{
    SqlWorker worker;
    QVariantHash result = worker.selectOne(u"SELECT id FROM work_session WHERE finished = false"_s);
    // There might be no session yet
    if (!result.isEmpty()) {
        mCurrentWorkSessionId = result.value(u"id"_s).toInt();
    }
    reloadSessionWorkTime();
}

void TimeController::start()
{
    if (mBreakTimer.isActive()) {
        emit breakFinished();
    }
    mBreakTimer.stop();
    setBreakTime(0);

    if (mCurrentProjectId < 0) {
        qWarning() << "Trying to run timer for not existing project";
        // TODO show warning display
        return;
    }
    if (mCurrentWorkSessionId < 0) {
        SqlWorker worker;
        const QVariantHash values {
            { u"start_time"_s, QDateTime::currentSecsSinceEpoch() }
        };
        worker.insert(u"work_session"_s, values);
        mCurrentWorkSessionId = worker.lastInsertId();
        mCurrentSessionWorkTime = 0;
        emit currentSessionWorkTimeChanged(mCurrentSessionWorkTime);
    }

    if (workTimeRunning()) {
        return;
    }

    insertWorkTimeToWorklogIfNotExists();

    mWorkTimer.start();
    emit workTimeRunningChanged(true);
}

void TimeController::pause()
{
    if (!workTimeRunning()) {
        return;
    }
    saveWorkTimeToWorklog();
    mWorkTimer.stop();
    emit workTimeRunningChanged(false);
}

void TimeController::reset()
{
    pause();
    setWorkTime(0);
    mCurrentSessionWorkTime = 0;
    emit currentSessionWorkTimeChanged(mCurrentSessionWorkTime);
    SqlWorker worker;
    const QVariantHash parameters {
        { u"finished"_s, true },
        { u"end_time"_s, QDateTime::currentSecsSinceEpoch() },
        { u"id"_s, mCurrentWorkSessionId }
    };
    worker.update(u"work_session"_s, { u"finished"_s, u"end_time"_s }, u"id=:id"_s, parameters);
    mCurrentWorkSessionId = -1;
}

int TimeController::projectWorkTime(const int projectId) const
{
    if (mCurrentWorkSessionId < 0) {
        return 0;
    }

    SqlWorker worker;
    const QVariantHash parameters {
        { u"session_id"_s, mCurrentWorkSessionId },
        { u"project_id"_s, projectId }
    };
    const QVariantHash result = worker.selectOne(u"SELECT work_time FROM worklog WHERE project_id=:project_id AND session_id=:session_id"_s, parameters);
    if (!result.isEmpty()) {
        return result.value(u"work_time"_s).toInt();
    }
    return 0;
}

int TimeController::workTime() const
{
    return mWorkTime;
}

void TimeController::setWorkTime(const int time)
{
    mWorkTime = time;
    emit workTimeChanged(mWorkTime);
    saveWorkTimeToWorklog();
    reloadSessionWorkTime();
}

int TimeController::maxWorkTime() const
{
    return mMaxWorkTime;
}

void TimeController::setMaxWorkTime(const int time)
{
    mMaxWorkTime = time;
    emit maxWorkTimeChanged(mMaxWorkTime);
}

bool TimeController::workTimeRunning() const
{
    return mWorkTimer.isActive();
}

void TimeController::setWorkTimeRunning(const bool running)
{
    if (running) {
        start();
    } else {
        pause();
    }
}

int TimeController::breakTime() const
{
    return mBreakTime;
}

void TimeController::setBreakTime(const int time)
{
    mBreakTime = time;
    emit breakTimeChanged(mBreakTime);
}

int TimeController::currentSessionWorkTime() const
{
    return mCurrentSessionWorkTime;
}

void TimeController::setCurrentSessionWorkTime(const int)
{
    // Cannot be set from outside
}

void TimeController::onCurrentProjectChanged(const int projectId, const int maxWorkTime)
{
    const bool timerRunning = workTimeRunning();
    if (timerRunning) {
        saveWorkTimeToWorklog();
    }
    mCurrentProjectId = projectId;
    if (projectId < 0) {
        setWorkTime(0);
        setMaxWorkTime(0);
        return;
    }
    if (timerRunning) {
        insertWorkTimeToWorklogIfNotExists();
    }
    mWorkTime = projectWorkTime(projectId);
    emit workTimeChanged(mWorkTime);
    setMaxWorkTime(maxWorkTime);
    if (timerRunning) {
        reloadSessionWorkTime();
    }
}

void TimeController::onCurrentProjectMaxWorkTimeChanged(const int maxWorkTime)
{
    setMaxWorkTime(maxWorkTime);
}

void TimeController::startBreak()
{
    setBreakTime(0);
    mBreakTimer.start();
    pause();
    emit breakStarted();
}

void TimeController::onWorkTimerTimeout()
{
    setWorkTime(mWorkTime + 1);
    // Update session time
    ++mCurrentSessionWorkTime;
    emit currentSessionWorkTimeChanged(mCurrentSessionWorkTime);
    // Update save
    ++mTimeSinceLastSave;
    if (mTimeSinceLastSave > SAVE_INTERVAL_SEC) {
        saveWorkTimeToWorklog();
    }
}

void TimeController::onBreakTimerTimeout()
{
    setBreakTime(mBreakTime + 1);
}

void TimeController::onRequestSaveWorklog()
{
    // If it is not running that means it is already saved
    if (!workTimeRunning()) {
        return;
    }
    saveWorkTimeToWorklog();
}

void TimeController::saveWorkTimeToWorklog()
{
    SqlWorker worker;
    const QVariantHash parameters {
        { u"work_time"_s, workTime() },
        { u"project_id"_s, mCurrentProjectId },
        { u"session_id"_s, mCurrentWorkSessionId },
        { u"update_time"_s, QDateTime::currentSecsSinceEpoch() }
    };
    worker.update(u"worklog"_s, { u"work_time"_s, u"update_time"_s }, u"project_id=:project_id AND session_id=:session_id"_s, parameters);
    mTimeSinceLastSave = 0;
}

void TimeController::insertWorkTimeToWorklogIfNotExists()
{
    SqlWorker worker;
    const QVariantHash worklogParamters {
        { u"session_id"_s, mCurrentWorkSessionId },
        { u"project_id"_s, mCurrentProjectId }
    };
    const QVariantHash worklogResults = worker.selectOne(u"SELECT id FROM worklog WHERE session_id=:session_id AND project_id=:project_id"_s, worklogParamters);
    if (worklogResults.isEmpty()) {
        const QVariantHash values {
            { u"project_id"_s, mCurrentProjectId },
            { u"session_id"_s, mCurrentWorkSessionId },
            { u"start_time"_s, QDateTime::currentSecsSinceEpoch() },
            { u"update_time"_s, QDateTime::currentSecsSinceEpoch() }
        };
        worker.insert(u"worklog"_s, values);
    }
}

void TimeController::reloadSessionWorkTime()
{
    int workTime = 0;
    if (mCurrentWorkSessionId >= 0) {
        SqlWorker worker;
        const QVariantHash paramters {
            { u"session_id"_s, mCurrentWorkSessionId }
        };
        const QVariantHash worklogResults = worker.selectOne(u"SELECT sum(work_time) as work_time_sum FROM worklog WHERE session_id=:session_id"_s, paramters);
        if (!worklogResults.isEmpty()) {
            workTime = worklogResults.value(u"work_time_sum"_s).toInt();
        }
    }

    mCurrentSessionWorkTime = workTime;
    emit currentSessionWorkTimeChanged(mCurrentSessionWorkTime);
}
