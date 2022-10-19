#include "QtSingleApp.h"

#include <QLocalSocket>

namespace {
const auto SERVER_NAME = QLatin1String("TIMRO_SINGLE_APP");
const auto PING_COMMAND = QLatin1String("TIMRO_PING");
}

QtSingleApp::QtSingleApp()
{
    connect(&mServer, &QLocalServer::newConnection, [this]() {
        while (mServer.hasPendingConnections()) {
            connect(mServer.nextPendingConnection(), &QLocalSocket::readyRead, this, &QtSingleApp::checkPing);
        }
    });
}

QtSingleApp::~QtSingleApp()
{
    disconnect(); // Disconnect all signals
}

bool QtSingleApp::tryRun()
{
    if (isAnotherServerRunning()) {
        return false;
    }
    if (!runLocalServer()) {
        return false;
    }
    return true;
}

bool QtSingleApp::isAnotherServerRunning()
{
    QLocalSocket testSocket;
    testSocket.connectToServer(SERVER_NAME, QLocalSocket::WriteOnly);
    auto connected = testSocket.waitForConnected();
    if (connected) {
        // ping another instance
        testSocket.write(PING_COMMAND.data());
        testSocket.waitForBytesWritten();
        testSocket.disconnectFromServer();
        if (testSocket.state() != QLocalSocket::UnconnectedState) {
            testSocket.waitForDisconnected();
        }
        return true;
    }

    return false;
}

bool QtSingleApp::runLocalServer()
{
    bool success = mServer.listen(SERVER_NAME);
    if (!success && mServer.serverError() == QAbstractSocket::AddressInUseError) {
        QLocalServer::removeServer(SERVER_NAME);
        success = mServer.listen(SERVER_NAME);
    }
    return success;
}

void QtSingleApp::checkPing()
{
    QLocalSocket *socket = dynamic_cast<QLocalSocket*>(sender());
    Q_ASSERT(socket);
    if (!socket) {
        qCritical() << "sender is not a socket!";
        return;
    }

    auto readedData = socket->readAll();
    if (readedData.startsWith(PING_COMMAND.data())) {
        qDebug() << "Another app just started.";
        emit anotherAppStarted();
    }

    socket->deleteLater();
}

