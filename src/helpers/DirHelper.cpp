#include "DirHelper.h"

#include <QStandardPaths>
#include <QDir>

DirHelper::DirHelper()
{

}

void DirHelper::prepareWorkDirectories()
{
    QDir dir;
    if (!dir.exists(workDir())) {
        dir.mkdir(workDir());
    }
    if (!dir.exists(dataDir())) {
        dir.mkdir(dataDir());
    }
}

QString DirHelper::dataDir()
{
    return workDir() + "data/";
}

QString DirHelper::workDir()
{
    return QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).absolutePath() + "/";
}
