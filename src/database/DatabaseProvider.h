#ifndef DATABASEPROVIDER_H
#define DATABASEPROVIDER_H

#include <QSqlDatabase>

class DatabaseProvider
{
public:
    enum class DatabaseType {
        Sqlite
    };

    static void setDefaultDatabaseType(const DatabaseType type);

    static QSqlDatabase getDatabase();
    static void closeDatabase(QSqlDatabase *database);

private:
    DatabaseProvider() = default;

    static DatabaseType databaseType;
};

#endif // DATABASEPROVIDER_H
