#ifndef SQLWORKER_H
#define SQLWORKER_H

#include <QSqlDatabase>
#include <QVariantHash>

class SqlWorker
{
public:
    enum class QueryStatus {
        Fail,
        Success,
        Unknown
    };

    SqlWorker();
    SqlWorker(QSqlDatabase database);
    ~SqlWorker();

    bool runQuery(const QString &queryString, const QVariantHash &parameters = QVariantHash());

    QVariantHash selectOne(const QString &selectQuery, const QVariantHash &parameters = QVariantHash());
    QVector<QSqlRecord> select(const QString &queryString);

    bool insert(const QString &tableName, const QVariantHash &values);
    bool remove(const QString &tableName, const QString &whereQuery, const QVariantHash &parameters);
    bool update(const QString &tableName, const QStringList &columns, const QString &whereQueryPart, const QVariantHash &parameters);

    QString lastError() const;

    QueryStatus lastQueryStatus() const;

    int lastInsertId() const;
    void clearLastInsertId();

private:
    bool mSpecificDatabseProvided = false;
    int mLastInsertedId = false;
    QString mLastError;
    QueryStatus mLastQueryStatus = QueryStatus::Fail;
    QSqlDatabase mDatabase;

    void updateLastError(QSqlQuery &query);
    void bindQueryParameters(QSqlQuery &query, const QVariantHash &parameters);
    QVariantHash parseSqlRecord(const QSqlRecord &record);

    QString prepareInsertQuery(const QString &tableName, const QVariantHash &properties);
    QString prepareDeleteQuery(const QString &tableName, const QString &whereQuery);
    QString prepareUpdateQuery(const QString &tableName, const QStringList &columns, const QString &whereQueryPart);
};

#endif // SQLWORKER_H
