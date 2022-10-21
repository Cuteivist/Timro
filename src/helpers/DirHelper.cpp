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
        const bool result = dir.mkdir(workDir());
        qInfo() << "Creating work dir" << workDir() << result;
    }
    if (!dir.exists(dataDir())) {
        const bool result = dir.mkdir(dataDir());
        qInfo() << "Creating data dir" << dataDir() << result;
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
