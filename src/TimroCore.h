#ifndef TIMROCORE_H
#define TIMROCORE_H

#include "controllers/ProjectController.h"
#include "controllers/TimeController.h"

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

private: // methods
    void init();

    void initManagers();
    void loadQml();
    void initDatabase();
};

#endif // TIMROCORE_H
