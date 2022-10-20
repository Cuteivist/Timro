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
    if (mCurrentProjectId > 0) {
        emit currentProjectChanged(mCurrentProjectId, mProjectModel.maxWorkTime(mCurrentProjectId));
    } else {
        setCurrentProjectId(mProjectModel.lastCreatedProjectId());
    }

    connect(&mProjectModel, &ProjectModel::projectRemoved, this, &ProjectController::onProjectRemoved);
    connect(&mProjectModel, &ProjectModel::projectAdded, this, &ProjectController::onProjectAdded);
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

void ProjectController::onProjectRemoved(const int projectId)
{
    if (projectId != mCurrentProjectId) {
        return;
    }
    // Current selected project was removed. Re-select new project
    setCurrentProjectId(mProjectModel.lastCreatedProjectId());
}

void ProjectController::onProjectAdded(const int projectId, const QString &)
{
    if (mCurrentProjectId > 0) {
        return;
    }
    // No project was selected. Auto select newly added project
    setCurrentProjectId(projectId);
}
