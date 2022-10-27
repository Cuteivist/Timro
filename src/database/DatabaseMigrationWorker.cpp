#include "DatabaseMigrationWorker.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QString>

#include "DatabaseProvider.h"
#include "DatabaseCleaner.h"

using namespace Qt::Literals::StringLiterals;

bool DatabaseMigrationWorker::initializeDatabase(QSqlDatabase database)
{
    if (!migrateDatabase(database)) {
        qCritical() << "Failed on migrateDatabase";
        return false;
    }
    return true;
}

bool DatabaseMigrationWorker::migrateDatabase(QSqlDatabase database)
{
    const bool dbCreated = database.isValid();
    if (!database.isValid()) {
        database = DatabaseProvider::getDatabase();
    }
    DatabaseCleaner cleaner(dbCreated ? &database : nullptr);

    QSqlQuery query(database);

    int currentVersion = 0;
    query.prepare(u"SELECT max(version) FROM db_info"_s);
    if (query.exec() && query.next()) {
        currentVersion = query.record().value(0).toInt();
    }

    const QStringList migrations = DatabaseMigrationWorker::migrations();
    if (currentVersion >= migrations.size()) {
        qInfo() << "Database is up to date. Skipping migrations";
        return true;
    }
    for (int i = currentVersion ; i < migrations.size() ; ++i) {
        const QStringList queryList = migrations.at(i).split(';', Qt::SkipEmptyParts);
        database.transaction();
        bool migrationFailed = false;
        for (const QString &queryString : queryList) {
            query.prepare(queryString);
            if (!query.exec()) {
                migrationFailed = true;
                break;
            }
        }

        if (migrationFailed) {
            qCritical() << "Migration failed. Rolling back transaction" << query.lastError() << database.rollback();
            return false;
        }

        if (!database.commit()) {
            qCritical() << "Transaction commit failed" << database.lastError().text();
            qCritical() << "Rolling back transaction" << database.rollback();
            return false;
        }

        query.prepare(u"INSERT INTO db_info (version) VALUES (%1)"_s.arg(i+1));
        if (!query.exec()) {
            qCritical() << "Failed to update db version!";
            return false;
        }
        qInfo() << "Successfully applied migration" << (i+1);
    }
    return true;
}

QStringList DatabaseMigrationWorker::migrations()
{
    QStringList migrations;

    migrations.insert(0, u"CREATE TABLE IF NOT EXISTS project ("
                         "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                         "name TEXT NOT NULL,"
                         "max_work_time INTEGER NOT NULL DEFAULT(0),"
                         "is_current INTERGER NOT NULL DEFAULT(0),"
                         "selected_task_id INTEGER DEFAULT(-1),"
                         "deleted INTEGER NOT NULL DEFAULT(0)"
                         ");"
                         "CREATE TABLE IF NOT EXISTS task ("
                         "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                         "name TEXT NOT NULL,"
                         "project_id INTEGER NOT NULL,"
                         "max_work_time INTEGER NOT NULL DEFAULT(0),"
                         "deleted INTEGER NOT NULL DEFAULT(0),"
                         "FOREIGN KEY(project_id) REFERENCES project(id) ON DELETE CASCADE"
                         ");"
                         "CREATE TABLE IF NOT EXISTS work_session ("
                         "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                         "start_time INTEGER DEFAULT(0),"
                         "end_time INTEGER DEFAULT(0),"
                         "finished INTEGER DEFAULT(0)"
                         ");"
                         "CREATE TABLE IF NOT EXISTS worklog ("
                         "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                         "project_id INTEGER NOT NULL,"
                         "session_id INTEGER NOT NULL,"
                         "task_id INTEGER,"
                         "start_time INTEGER DEFAULT(0),"
                         "work_time INTEGER DEFAULT(0),"
                         "update_time INTEGER DEFAULT(0),"
                         "FOREIGN KEY(project_id) REFERENCES project(id) ON DELETE CASCADE,"
                         "FOREIGN KEY(task_id) REFERENCES task(id) ON DELETE CASCADE,"
                         "FOREIGN KEY(session_id) REFERENCES work_session(id) ON DELETE CASCADE"
                         ");"
                         "CREATE TABLE IF NOT EXISTS db_info ("
                         "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                         "version INTEGER NOT NULL DEFAULT(1),"
                         "changelog TEXT NOT NULL DEFAULT 'initial migration'"
                         ");"_s);

    return migrations;
}
