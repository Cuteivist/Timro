#include "ProjectController.h"

#include "models/ProjectModel.h"

using namespace Qt::Literals::StringLiterals;

ProjectController::ProjectController(QObject *parent)
    : QObject(parent)
{
}

void ProjectController::init()
{
    mCurrentProjectId = mProjectModel.currentProjectId();
    emit currentProjectChanged(mCurrentProjectId, mProjectModel.maxWorkTime(mCurrentProjectId));
}

ProjectModel *ProjectController::model()
{
    return &mProjectModel;
}

int ProjectController::currentProjectId() const
{
    return mCurrentProjectId;
}

void ProjectController::setCurrentProjectId(const int projectId)
{
    if (projectId == mCurrentProjectId) {
        return;
    }
    if (!mProjectModel.changeCurrentProject(projectId)) {
        qWarning() << "Unable to change current project!";
    }
    mCurrentProjectId = projectId;
    emit currentProjectIdChanged(mCurrentProjectId);
    emit currentProjectChanged(mCurrentProjectId, mProjectModel.maxWorkTime(mCurrentProjectId));
}
