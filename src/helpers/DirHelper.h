#ifndef DIRHELPER_H
#define DIRHELPER_H

#include <QString>

class DirHelper
{
public:
    DirHelper();

    static void prepareWorkDirectories();

    static QString dataDir();
    static QString workDir();
};

#endif // DIRHELPER_H
