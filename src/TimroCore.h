#ifndef TIMROCORE_H
#define TIMROCORE_H

#include "controllers/ProjectController.h"
#include "controllers/TimeController.h"
#include "controllers/TrayController.h"
#include "helpers/QmlHelper.h"

#include <QObject>
#include <QQmlApplicationEngine>

class TimroCore : public QObject
{
    Q_OBJECT
public:
    explicit TimroCore(QObject *parent = nullptr);
    Q_DISABLE_COPY(TimroCore)

    void init(QQmlApplicationEngine &engine);

private: // members
    QQmlApplicationEngine *mEngine {};

    TimeController mTimeController;
    ProjectController mProjectController;
    TrayController mTrayController;
    QmlHelper mQmlHelper;

signals:
    void anotherAppStarted() const;

private: // methods
    void connectManagers();
    void initManagers();
    void loadQml();
    void initDatabase();
};

#endif // TIMROCORE_H
