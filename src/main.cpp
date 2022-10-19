#include <QGuiApplication>>

#include "TimroCore.h"
#include "QtSingleApp.h"
#include "database/DatabaseProvider.h"
#include "helpers/DirHelper.h"

int main(int argc, char *argv[])
{
    // TODO start Qt single app
    using namespace Qt::Literals::StringLiterals;
    DatabaseProvider::setDefaultDatabaseType(DatabaseProvider::DatabaseType::Sqlite);
    DirHelper::prepareWorkDirectories();

    QGuiApplication app(argc, argv);
    app.setApplicationName(u"Timro"_s);

    QtSingleApp singleApp;
    if (!singleApp.tryRun()) {
        qDebug() << "Another app is running!";
        return 1;
    }

    TimroCore core;

    // TODO connect singleApp to tray manager to show show window when second app started
    return app.exec();
}
