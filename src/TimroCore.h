#ifndef TIMROCORE_H
#define TIMROCORE_H

#include "controllers/ProjectController.h"
#include "controllers/TimeController.h"
#include "controllers/TrayController.h"

#include <QObject>
#include <QQmlApplicationEngine>

class TimroCore : public QObject
{
    Q_OBJECT
public:
    explicit TimroCore(QObject *parent = nullptr);

private: // members
    QQmlApplicationEngine mEngine;

    TimeController mTimeController;
    ProjectController mProjectController;
    TrayController mTrayController;

signals:
    void anotherAppStarted() const;

private: // methods
    void init();

    void connectManagers();
    void initManagers();
    void loadQml();
    void initDatabase();
};

#endif // TIMROCORE_H
