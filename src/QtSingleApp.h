#ifndef QTSINGLEAPP_H
#define QTSINGLEAPP_H

#include <QLocalServer>
#include <QObject>

class QtSingleApp : public QObject
{
    Q_OBJECT
public:
    explicit QtSingleApp();
    ~QtSingleApp();

    bool tryRun();

signals:
    void anotherAppStarted() const;

private:
    QLocalServer mServer;

    bool isAnotherServerRunning();
    bool runLocalServer();

    void checkPing();
};

#endif // QTSINGLEAPP_H
