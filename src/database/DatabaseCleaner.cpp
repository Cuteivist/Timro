#include "DatabaseCleaner.h"

#include "DatabaseProvider.h"

DatabaseCleaner::DatabaseCleaner(QSqlDatabase *database)
    : mDatabase(database)
{

}

DatabaseCleaner::~DatabaseCleaner()
{
    cleanup();
}

void DatabaseCleaner::cleanup()
{
    if (mDatabase == nullptr) {
        return;
    }
    DatabaseProvider::closeDatabase(mDatabase);
    mDatabase = nullptr;
}
