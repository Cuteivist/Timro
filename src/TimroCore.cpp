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
    initManagers();
    loadQml();
}

void TimroCore::initManagers()
{
    connect(&mProjectController, &ProjectController::currentProjectChanged, &mTimeController, &TimeController::onCurrentProjectChanged);
    connect(mProjectController.model(), &ProjectModel::currentProjectMaxWorkTimeChanged, &mTimeController, &TimeController::onCurrentProjectMaxWorkTimeChanged);

    mEngine.rootContext()->setContextProperty(u"projectController"_s, &mProjectController);
    mEngine.rootContext()->setContextProperty(u"timeController"_s, &mTimeController);

    // Time controller need to be initialized first
    mTimeController.init();
    mProjectController.init();
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
        // TODO show some error message ?
    }
    DatabaseProvider::getDatabase().close();
}
