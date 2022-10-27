#include "SqliteDatabaseProvider.h"

#include <QDebug>
#include <QUuid>
#include <QSqlError>

#include "helpers/DirHelper.h"

using namespace Qt::Literals::StringLiterals;

QSqlDatabase SqliteDatabaseProvider::getDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(u"QSQLITE"_s, QUuid::createUuid().toString(QUuid::WithoutBraces));
#ifdef QT_DEBUG
    db.setDatabaseName(DirHelper::dataDir() + u"timro_debug.db"_s);
#else
    db.setDatabaseName(DirHelper::dataDir() + u"timro.db"_s);
#endif
    if (!db.open()) {
        qCritical() << db.lastError();
    }
    return db;
}
