#include "ProjectModel.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QByteArray>

using namespace Qt::Literals::StringLiterals;

ProjectModel::ProjectModel(QObject *parent)
    : SqlModel(parent)
{
}

ProjectModel::~ProjectModel()
{
}

bool ProjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!SqlModel::setData(index, value, role)) {
        return false;
    }

    if (role == MaxWorkTimeRole && data(index, IsCurrentRole).toBool()) {
        emit currentProjectMaxWorkTimeChanged(value.toInt());
    }
    return true;
}

QHash<int, QByteArray> ProjectModel::roleNames() const
{
    static const QHash<int, QByteArray> roleNames {
        { IdRole, "id"_ba },
        { NameRole, "name"_ba },
        { MaxWorkTimeRole, "maxWorkTime"_ba },
        { IsCurrentRole, "isCurrent"_ba },
        { SelectedTaskIdRole, "selectedTask"_ba },
        { DeletedRole, "deleted"_ba }
    };
    return roleNames;
}

void ProjectModel::init()
{
    setTable(u"project"_s);
    setEditStrategy(QSqlTableModel::OnFieldChange);
    select();
    setFilter(u"deleted=0"_s);
}

bool ProjectModel::changeCurrentProject(const int id)
{
    QModelIndex modelIndex = modelIndexFromId(id);
    if (!modelIndex.isValid()) {
        return false;
    }
    setEditStrategy(QSqlTableModel::OnManualSubmit);

    for (int i = 0 ; i < rowCount() ; ++i) {
        setData(index(i, 0), false, IsCurrentRole);
    }
    setData(modelIndex, true, IsCurrentRole);
    const bool result = submitAll();
    if (!result) {
        revertAll();
    }

    setEditStrategy(QSqlTableModel::OnFieldChange);
    return result;
}

void ProjectModel::resetCurrentProject()
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    for (int i = 0 ; i < rowCount() ; ++i) {
        setData(index(i, 0), false, IsCurrentRole);
    }
    const bool result = submitAll();
    if (!result) {
        revertAll();
    }
    setEditStrategy(QSqlTableModel::OnFieldChange);
}

int ProjectModel::currentProjectId()
{
    if (rowCount() == 0) {
        return -1;
    }
    for (int i = 0 ; i < rowCount() ; ++i) {
        QModelIndex modelIndex = index(i, 0);
        if (data(modelIndex, IsCurrentRole).toBool() && !data(modelIndex, DeletedRole).toBool()) {
            return data(modelIndex, IdRole).toInt();
        }
    }
    return -1;
}

int ProjectModel::lastCreatedProjectId()
{
    for (int i = rowCount() - 1 ; i >= 0 ; --i) {
        QModelIndex modelIndex = index(i, 0);
        if (!data(modelIndex, DeletedRole).toBool()) {
            return data(modelIndex, IdRole).toInt();
        }
    }
    return -1;
}

QHash<int, QString> ProjectModel::projectList() const
{
    QHash<int, QString> result;
    const int count = rowCount();
    result.reserve(count);
    for (int i = 0 ; i < count ; ++i) {
        QModelIndex modelIndex = index(i, 0);
        result.insert(data(modelIndex, IdRole).toInt(), data(modelIndex, NameRole).toString());
    }
    return result;
}

bool ProjectModel::add(const QString &name, const int maxWorkTime)
{
    QSqlRecord newRecord = record();
    newRecord.setValue(roleToColumnIndex(NameRole), name);
    newRecord.setValue(roleToColumnIndex(MaxWorkTimeRole), maxWorkTime);
    newRecord.setValue(roleToColumnIndex(IsCurrentRole), false);
    newRecord.setValue(roleToColumnIndex(SelectedTaskIdRole), -1);
    newRecord.setValue(roleToColumnIndex(DeletedRole), false);
    newRecord.remove(roleToColumnIndex(IdRole));
    const bool result = insertNewRecord(newRecord);
    if (result) {
        const int id = data(index(rowCount() - 1, 0), IdRole).toInt();
        emit projectAdded(id, name);
    } else {
        qWarning() << "Insert projet failed" << name << lastError();
    }
    return result;
}

bool ProjectModel::exists(const QString &name) const
{
    for (int i = 0 ; i < rowCount() ; ++i) {
        if (data(index(i, 0), NameRole).toString() == name && !data(index(i, 0), DeletedRole).toBool()) {
            return true;
        }
    }
    return false;
}

bool ProjectModel::update(const int id, const QString &name, const int maxWorkTime)
{
    QModelIndex index = modelIndexFromId(id);
    if (!index.isValid()) {
        return false;
    }
    if (data(index, NameRole).toString() != name) {
        setData(index, name, NameRole);
        emit projectRenamed(id, name);
    }
    if (data(index, MaxWorkTimeRole).toInt() != maxWorkTime) {
        setData(index, maxWorkTime, MaxWorkTimeRole);
    }
    return false;
}

bool ProjectModel::remove(const int id)
{
    QModelIndex index = modelIndexFromId(id);
    if (!index.isValid()) {
        return false;
    }
    setData(index, true, DeletedRole);
    // Re-apply filters
    select();
    emit projectRemoved(id);
    return true;
}

QString ProjectModel::name(const int id) const
{
    QModelIndex modelIndex = modelIndexFromId(id);
    return data(index(modelIndex.row(), 0), NameRole).toString();
}

int ProjectModel::maxWorkTime(const int id) const
{
    QModelIndex modelIndex = modelIndexFromId(id);
    return data(index(modelIndex.row(), 0), MaxWorkTimeRole).toInt();
}

QModelIndex ProjectModel::modelIndexFromId(const int id) const
{
    for(int i = 0; i < rowCount(); ++i) {
        if (data(index(i, 0), IdRole).toInt() == id) {
            return index(i, roleToColumnIndex(IdRole));
        }
    }
    return {};
}
