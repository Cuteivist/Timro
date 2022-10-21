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
}

void TimeController::start()
{
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
    }
    if (mWorkTimer.isActive()) {
        return;
    }

    SqlWorker worker;
    const QVariantHash worklogParamters {
        { u"session_id"_s, mCurrentWorkSessionId },
        { u"project_id"_s, mCurrentProjectId }
    };
    const QVariantHash worklogResults = worker.selectOne(u"SELECT id WHERE session_id=:session_id AND project_id=:project_id"_s, worklogParamters);
    if (worklogResults.isEmpty()) {
        const QVariantHash values {
            { u"project_id"_s, mCurrentProjectId },
            { u"session_id"_s, mCurrentWorkSessionId },
            { u"start_time"_s, QDateTime::currentSecsSinceEpoch() }
        };
        worker.insert(u"worklog"_s, values);
    }

    mWorkTimer.start();
    emit runningChanged(true);
}

void TimeController::pause()
{
    if (!mWorkTimer.isActive()) {
        return;
    }
    saveWorkTimeToWorklog();
    mWorkTimer.stop();
    emit runningChanged(false);
}

void TimeController::reset()
{
    pause();
    setWorkTime(0);
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

bool TimeController::running() const
{
    return mWorkTimer.isActive();
}

void TimeController::setRunning(const bool running)
{
    if (running) {
        start();
    } else {
        pause();
    }
}

void TimeController::onCurrentProjectChanged(const int projectId, const int maxWorkTime)
{
    if (projectId < 0) {
        qWarning() << "Invalid project id";
        return;
    }
    if (running()) {
        saveWorkTimeToWorklog();
    }
    mCurrentProjectId = projectId;
    setWorkTime(projectWorkTime(projectId));
    setMaxWorkTime(maxWorkTime);
}

void TimeController::onCurrentProjectMaxWorkTimeChanged(const int maxWorkTime)
{
    setMaxWorkTime(maxWorkTime);
}

void TimeController::startBreak()
{
    pause();
    emit breakStarted();
}

void TimeController::onWorkTimerTimeout()
{
    setWorkTime(mWorkTime + 1);
    ++mTimeSinceLastSave;
    if (mTimeSinceLastSave > SAVE_INTERVAL_SEC) {
        saveWorkTimeToWorklog();
    }
}

void TimeController::onRequestSaveWorklog()
{
    // If it is not running that means it is already saved
    if (!running()) {
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
        { u"session_id"_s, mCurrentWorkSessionId }
    };
    worker.update(u"worklog"_s, { u"work_time"_s }, u"project_id=:project_id AND session_id=:session_id"_s, parameters);
    mTimeSinceLastSave = 0;
}
