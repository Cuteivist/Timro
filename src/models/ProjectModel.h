#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include "SqlModel.h"

class ProjectModel : public SqlModel
{
    Q_OBJECT
public:
    enum ModelRole {
        IdRole = Qt::UserRole + 1,
        NameRole,
        MaxWorkTimeRole,
        IsCurrentRole,
        SelectedTaskIdRole,
        DeletedRole
    };

    explicit ProjectModel(QObject *parent = nullptr);
    ~ProjectModel() override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    void init();

    bool changeCurrentProject(const int id);
    void resetCurrentProject();
    int currentProjectId();

    int lastCreatedProjectId();

    QHash<int, QString> projectList() const;

    Q_INVOKABLE bool add(const QString &name, const int maxWorkTime);
    Q_INVOKABLE bool exists(const QString &name) const;
    Q_INVOKABLE bool update(const int id, const QString &name, const int maxWorkTime);
    Q_INVOKABLE bool remove(const int id);

    Q_INVOKABLE QString name(const int id) const;
    Q_INVOKABLE int maxWorkTime(const int id) const;

signals:
    void currentProjectMaxWorkTimeChanged(const int maxWorkTime) const;
    void projectAdded(const int projectId, const QString &name) const;
    void projectRemoved(const int projectId) const;
    void projectRenamed(const int projectId, const QString &name) const;

private:
    QModelIndex modelIndexFromId(const int id) const;  
};

#endif // PROJECTMODEL_H
