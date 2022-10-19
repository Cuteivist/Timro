#include "SqlWorker.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "database/DatabaseProvider.h"

using namespace Qt::Literals::StringLiterals;

SqlWorker::SqlWorker()
{
    mDatabase = DatabaseProvider::getDatabase();
}

SqlWorker::SqlWorker(QSqlDatabase database)
{
    mSpecificDatabseProvided = true;
    if (!database.isValid()) {
        mDatabase = DatabaseProvider::getDatabase();
        mSpecificDatabseProvided = false;
    }
    if (!database.isOpen() && !database.open()) {
        qWarning() << "Failed to open database";
    }
}

SqlWorker::~SqlWorker()
{
    if (mSpecificDatabseProvided) {
        if (mDatabase.isOpen() && QSqlDatabase::contains(mDatabase.connectionName())) {
            qWarning() << "Database is not released from SqlWorker. Current connection count =" << QSqlDatabase::connectionNames().count();
        }
        return;
    }
    DatabaseProvider::closeDatabase(&mDatabase);
}

bool SqlWorker::runQuery(const QString &queryString, const QVariantHash &parameters)
{
    mLastQueryStatus = QueryStatus::Fail;
    {
        QSqlQuery query(mDatabase);
        query.setForwardOnly(true);
        if (!query.prepare(queryString)) {
            updateLastError(query);
            return false;
        }

        bindQueryParameters(query, parameters);

        if (!query.exec()) {
            updateLastError(query);
            qWarning() << "Query exec error:" << mLastError << "  ||  " << parameters << queryString;
            return false;
        }

        const QVariant lastInsertId = query.lastInsertId();
        if (lastInsertId.isValid()) {
            mLastInsertedId = lastInsertId.toInt();
        }

        mLastQueryStatus = QueryStatus::Success;
        query.clear();
    }

    return true;
}

QVariantHash SqlWorker::selectOne(const QString &selectQuery, const QVariantHash &parameters)
{
    QVariantHash result;
    mLastQueryStatus = QueryStatus::Fail;
    {
        QSqlQuery query(mDatabase);

        if (!query.prepare(selectQuery)) {
            updateLastError(query);
            return result;
        }

        bindQueryParameters(query, parameters);

        if (!query.exec()) {
            updateLastError(query);
            qWarning() << "Query exec error:" << mLastError;
            return result;
        }

        if (!query.next()) {
            return result;
        }

        const QSqlRecord &sqlRecord = query.record();
        result = parseSqlRecord(sqlRecord);
        mLastQueryStatus = QueryStatus::Success;
        query.clear();
    }
    return result;
}

QVector<QSqlRecord> SqlWorker::select(const QString &queryString)
{
    QVector<QSqlRecord> records;
    mLastQueryStatus = QueryStatus::Fail;

    if (queryString.contains(u"SELECT"_s)) {
        qWarning() << "Query is invalid!";
        return records;
    }

    {
        QSqlQuery query(mDatabase);
        if (!query.prepare(queryString)) {
            updateLastError(query);
            return records;
        }

        if (!query.exec()) {
            updateLastError(query);
            qWarning() << "Query exec error:" << mLastError;
            return records;
        }

        records.reserve(query.size());
        while(query.next()) {
            records.append(query.record());
        }

        mLastQueryStatus = QueryStatus::Success;
        query.clear();
    }

    return records;
}

bool SqlWorker::insert(const QString &tableName, const QVariantHash &values)
{
    if (values.isEmpty()) {
        qWarning() << "Nothing to insert!";
        return false;
    }

    if (tableName.isEmpty()) {
        qWarning() << "Table name is empty!";
        return false;
    }

    const QString insertQuery = prepareInsertQuery(tableName, values);
    clearLastInsertId();

    if (!runQuery(insertQuery, values)) {
        qWarning() << "Insert failed" << mLastError << " || " << values;
        return false;
    }
    return mLastQueryStatus == QueryStatus::Success;
}

bool SqlWorker::remove(const QString &tableName, const QString &whereQuery, const QVariantHash &parameters)
{
    const QString query = prepareDeleteQuery(tableName, whereQuery);
    return runQuery(query, parameters);
}

bool SqlWorker::update(const QString &tableName, const QStringList &columns, const QString &whereQueryPart, const QVariantHash &parameters)
{
    if (parameters.isEmpty()) {
        qWarning() << "Update failed, paramters are empty!";
        return false;
    }
    const QString query = prepareUpdateQuery(tableName, columns, whereQueryPart);
    return runQuery(query, parameters);
}

QString SqlWorker::lastError() const
{
    return mLastError;
}

SqlWorker::QueryStatus SqlWorker::lastQueryStatus() const
{
    return mLastQueryStatus;
}

int SqlWorker::lastInsertId() const
{
    return mLastInsertedId;
}

void SqlWorker::clearLastInsertId()
{
    mLastInsertedId = -1;
}

void SqlWorker::updateLastError(QSqlQuery &query)
{
    mLastError = query.lastError().text();
}

void SqlWorker::bindQueryParameters(QSqlQuery &query, const QVariantHash &parameters)
{
    const static QChar parameterOperator(':');
    const QStringList keys = parameters.keys();
    for (const auto &key : keys) {
        const QVariant &value = parameters.value(key);
        if (key.startsWith(parameterOperator)) {
            query.bindValue(key, value);
        } else {
            query.bindValue(parameterOperator + key, value);
        }
    }
}

QVariantHash SqlWorker::parseSqlRecord(const QSqlRecord &record)
{
    QVariantHash values;
    const int count = record.count();
    for (int i = 0 ; i < count ; i++) {
        values.insert(record.fieldName(i).toUtf8(), record.value(i));
    }
    return values;
}

QString SqlWorker::prepareInsertQuery(const QString &tableName, const QVariantHash &properties)
{
    const QStringList &keys = properties.keys();
    const QString bindableValues = QString(":%1").arg(keys.join(", :"));
    return u"INSERT INTO %1 (%2) VALUES (%3)"_s.arg(tableName).arg(keys.join(", ")).arg(bindableValues);
}

QString SqlWorker::prepareDeleteQuery(const QString &tableName, const QString &whereQuery)
{
    return u"DELETE FROM %1 WHERE %2"_s.arg(tableName, whereQuery);
}

QString SqlWorker::prepareUpdateQuery(const QString &tableName, const QStringList &columns, const QString &whereQueryPart)
{
    QStringList setList;
    setList.reserve(columns.size());
    for (const auto &column : columns) {
        setList.append(u"%1 = :%1"_s.arg(column));
    }
    return u"UPDATE %1 SET %2 WHERE %3"_s.arg(tableName, setList.join(','), whereQueryPart);
}
