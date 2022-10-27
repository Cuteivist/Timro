#include "SqlModel.h"

#include <QSqlError>

#include "database/DatabaseProvider.h"

SqlModel::SqlModel(QObject *parent)
    : QSqlTableModel(parent, DatabaseProvider::getDatabase())
{

}

SqlModel::~SqlModel()
{
}

QVariant SqlModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole || !index.isValid()) {
        return QSqlTableModel::data(index, role);
    }
    QModelIndex modelIndex = this->index(index.row(), roleToColumnIndex(role));
    return QSqlTableModel::data(modelIndex, Qt::DisplayRole);
}

bool SqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role < Qt::UserRole) {
        return QSqlTableModel::setData(index, value, role);
    }
    QModelIndex modelIndex = this->index(index.row(), roleToColumnIndex(role));
    return QSqlTableModel::setData(modelIndex, value, Qt::EditRole);
}

int SqlModel::roleToColumnIndex(const int role)
{
    return role - (Qt::UserRole + 1);
}

bool SqlModel::insertNewRecord(const QSqlRecord &record, const int row)
{
    setEditStrategy(QSqlTableModel::OnRowChange);
    const bool result = insertRecord(row, record);
    if (!result) {
        qWarning() << "SQL error:" << tableName() << lastError().text();
    }
    setEditStrategy(QSqlTableModel::OnFieldChange);
    return result;
}
