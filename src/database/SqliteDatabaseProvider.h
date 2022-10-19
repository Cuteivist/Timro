#ifndef SQLITEDATABASEPROVIDER_H
#define SQLITEDATABASEPROVIDER_H

#include <QSqlDatabase>

class SqliteDatabaseProvider
{
public:
    static QSqlDatabase getDatabase();

private:
    SqliteDatabaseProvider() = default;
};

#endif // SQLITEDATABASEPROVIDER_H
