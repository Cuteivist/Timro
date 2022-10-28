#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QObject>

#include "models/ProjectModel.h"
#include "models/ProjectWorkHistoryModel.h"

class ProjectController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ProjectModel *model READ model CONSTANT)
    Q_PROPERTY(ProjectWorkHistoryModel *workHistoryModel READ workHistoryModel CONSTANT)
    Q_PROPERTY(int currentProjectId READ currentProjectId WRITE setCurrentProjectId NOTIFY currentProjectIdChanged)
public:
    explicit ProjectController(QObject *parent = nullptr);
    Q_DISABLE_COPY(ProjectController)

    void init();

    ProjectModel *model();
    ProjectWorkHistoryModel *workHistoryModel();

    int currentProjectId() const;
    void setCurrentProjectId(const int projectId);

signals:
    void currentProjectChanged(const int projectId, const int maxWorkTime) const;
    void currentProjectIdChanged(const int currentProjectId) const;

private slots:
    void onProjectRemoved(const int projectId);
    void onProjectAdded(const int projectId, const QString &name);

private:
    int mCurrentProjectId = -1;
    ProjectModel mProjectModel;
    ProjectWorkHistoryModel mProjectWorkHistoryModel;
};

#endif // PROJECTCONTROLLER_H
