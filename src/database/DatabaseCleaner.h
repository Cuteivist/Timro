#ifndef DATABASECLEANER_H
#define DATABASECLEANER_H

#include <QObject>

class QSqlDatabase;

class DatabaseCleaner
{
public:
    DatabaseCleaner(QSqlDatabase *database);
    ~DatabaseCleaner();
    Q_DISABLE_COPY(DatabaseCleaner)

private:
    QSqlDatabase *mDatabase {};

    void cleanup();
};

#endif // DATABASECLEANER_H
