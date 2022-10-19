#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QObject>

#include "models/ProjectModel.h"

class ProjectController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ProjectModel *model READ model CONSTANT)
    Q_PROPERTY(int currentProjectId READ currentProjectId WRITE setCurrentProjectId NOTIFY currentProjectIdChanged)
public:
    explicit ProjectController(QObject *parent = nullptr);

    void init();

    ProjectModel *model();

    int currentProjectId() const;
    void setCurrentProjectId(const int projectId);

signals:
    void currentProjectChanged(const int projectId, const int maxWorkTime) const;
    void currentProjectIdChanged(const int currentProjectId) const;

private:
    int mCurrentProjectId = -1;
    ProjectModel mProjectModel;
};

#endif // PROJECTCONTROLLER_H
