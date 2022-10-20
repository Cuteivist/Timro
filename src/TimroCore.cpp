#include "TimroCore.h"

#include <QQmlContext>

#include "database/DatabaseMigrationWorker.h"
#include "database/DatabaseProvider.h"

using namespace Qt::Literals::StringLiterals;

TimroCore::TimroCore(QObject *parent)
    : QObject{parent}
{
    init();
}

void TimroCore::init()
{
    // Order of calls here is really important. Don't change it!
    initDatabase();
    connectManagers();
    initManagers();
    loadQml();
}

void TimroCore::connectManagers()
{
    // Core
    connect(this, &TimroCore::anotherAppStarted, &mTrayController, &TrayController::showWindow);

    // Project
    connect(&mProjectController, &ProjectController::currentProjectChanged, &mTimeController, &TimeController::onCurrentProjectChanged);
    connect(mProjectController.model(), &ProjectModel::currentProjectMaxWorkTimeChanged, &mTimeController, &TimeController::onCurrentProjectMaxWorkTimeChanged);
    connect(&mProjectController, &ProjectController::currentProjectChanged, &mTrayController, &TrayController::onCurrentProjectChanged);
    connect(mProjectController.model(), &ProjectModel::projectAdded, &mTrayController, &TrayController::onProjectAdded);
    connect(mProjectController.model(), &ProjectModel::projectRemoved, &mTrayController, &TrayController::onProjectRemoved);
    connect(mProjectController.model(), &ProjectModel::projectRenamed, &mTrayController, &TrayController::onProjectRenamed);

    // Time
    connect(&mTimeController, &TimeController::runningChanged, &mTrayController, &TrayController::runningChanged);
    connect(&mTimeController, &TimeController::workTimeChanged, &mTrayController, &TrayController::onWorkTimeChanged);

    // Tray
    connect(&mTrayController, &TrayController::toggleStartPause, this, [this]() {
        if (mTimeController.running()) {
            mTimeController.pause();
        } else {
            mTimeController.start();
        }
    });
    connect(&mTrayController, &TrayController::startBreak, &mTimeController, &TimeController::startBreak);
    connect(&mTrayController, &TrayController::currentProjectChanged, &mProjectController, &ProjectController::setCurrentProjectId);
    connect(&mTrayController, &TrayController::beforeQuit, &mTimeController, &TimeController::requestSaveWorklog);
}

void TimroCore::initManagers()
{
    mEngine.rootContext()->setContextProperty(u"projectController"_s, &mProjectController);
    mEngine.rootContext()->setContextProperty(u"timeController"_s, &mTimeController);
    mEngine.rootContext()->setContextProperty(u"trayController"_s, &mTrayController);

    // Time controller need to be initialized first
    mTimeController.init();
    mProjectController.init();

    mTrayController.initProjectMenuGroup(mProjectController.model()->projectList());
    mTrayController.onCurrentProjectChanged(mProjectController.currentProjectId());
}

void TimroCore::loadQml()
{
    const QUrl url(u"qrc:/Timro/qml/main.qml"_s);
    mEngine.load(url);
}

void TimroCore::initDatabase()
{
    if (!DatabaseMigrationWorker::initializeDatabase()) {
        qCritical() << "Failed to initialize databse";
        // TODO show error display
    }
    DatabaseProvider::getDatabase().close();
}
