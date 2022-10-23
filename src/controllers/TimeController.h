#ifndef TIMECONTROLLER_H
#define TIMECONTROLLER_H

#include <QObject>
#include <QTimer>

class TimeController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int workTime READ workTime WRITE setWorkTime NOTIFY workTimeChanged)
    Q_PROPERTY(int maxWorkTime READ maxWorkTime WRITE setMaxWorkTime NOTIFY maxWorkTimeChanged)
    Q_PROPERTY(bool workTimeRunning READ workTimeRunning WRITE setWorkTimeRunning NOTIFY workTimeRunningChanged)
    Q_PROPERTY(int breakTime READ breakTime WRITE setBreakTime NOTIFY breakTimeChanged)

public:
    explicit TimeController(QObject *parent = nullptr);

    void init();

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void reset();

    int projectWorkTime(const int projectId) const;

    int workTime() const;
    void setWorkTime(const int time);

    int maxWorkTime() const;
    void setMaxWorkTime(const int time);

    bool workTimeRunning() const;
    void setWorkTimeRunning(const bool running);

    int breakTime() const;
    void setBreakTime(const int time);

public slots:
    void onCurrentProjectChanged(const int projectId, const int maxWorkTime);
    void onCurrentProjectMaxWorkTimeChanged(const int maxWorkTime);

    void startBreak();

signals:
    void workTimeChanged(const int workTime) const;
    void maxWorkTimeChanged(const int workTime) const;
    void workTimeRunningChanged(const bool running) const;
    void breakTimeChanged(const int breakTime) const;
    void requestSaveWorklog() const;

    void breakStarted() const;

private slots:
    void onWorkTimerTimeout();
    void onBreakTimerTimeout();
    void onRequestSaveWorklog();

private:
    void saveWorkTimeToWorklog();

private:
    int mWorkTime {0};
    int mBreakTime {0};
    int mMaxWorkTime {60 * 60 * 8}; // 8 hours
    int mCurrentProjectId {-1};
    int mTimeSinceLastSave {0};
    int mCurrentWorkSessionId {-1};
    QTimer mWorkTimer, mBreakTimer;
};

#endif // TIMECONTROLLER_H
