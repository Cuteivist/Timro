#include "DatabaseProvider.h"

#include <QDebug>

#include "SqliteDatabaseProvider.h"

DatabaseProvider::DatabaseType DatabaseProvider::databaseType = DatabaseProvider::DatabaseType::Sqlite;

void DatabaseProvider::setDefaultDatabaseType(const DatabaseType type)
{
    databaseType = type;
}

QSqlDatabase DatabaseProvider::getDatabase()
{
    switch(databaseType) {
        default:
            qWarning() << "Requested not supported database. Using default sqlite";
            [[fallthrough]];
        case DatabaseProvider::DatabaseType::Sqlite:
            return SqliteDatabaseProvider::getDatabase();
        }
}

void DatabaseProvider::closeDatabase(QSqlDatabase *database)
{
    if (database == nullptr) {
        return;
    }
    const QString &connectionName = database->connectionName();
    database->close();
    *database = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}
