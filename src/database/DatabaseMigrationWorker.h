#ifndef DATABASEMIGRATIONWORKER_H
#define DATABASEMIGRATIONWORKER_H

#include <QSqlDatabase>

class DatabaseMigrationWorker
{
public:

    static bool initializeDatabase(QSqlDatabase database = QSqlDatabase());
    static bool migrateDatabase(QSqlDatabase database = QSqlDatabase());

private:
    static QStringList migrations();

    DatabaseMigrationWorker() = default;
};

#endif // DATABASEMIGRATIONWORKER_H
