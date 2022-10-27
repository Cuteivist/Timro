#include <QApplication>

#include <QDateTime>
#include <QFileInfo>
#include <iostream>

#include "TimroCore.h"
#include "QtSingleApp.h"
#include "database/DatabaseProvider.h"
#include "helpers/DirHelper.h"

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    using namespace Qt::Literals::StringLiterals;
    Q_UNUSED(context);

    static const QString messageEndColor = u"\e[0m"_s, contextStartColor = u"\e[37m"_s, contextEndColor = u"\e[0m"_s;
    QString messageTypeSymbol, messageStartColor;
    switch (type)
    {
    case QtDebugMsg:
        messageTypeSymbol = u"[D]"_s;
        messageStartColor.clear();
        break;
    case QtWarningMsg:
        messageTypeSymbol = u"[W]"_s;
        messageStartColor = u"\e[30m\e[43m"_s;
        break;
    case QtCriticalMsg:
        messageTypeSymbol = u"[C]"_s;
        messageStartColor = u"\e[41m"_s;
        break;
    case QtFatalMsg:
        messageTypeSymbol = u"[F]"_s;
        messageStartColor = u"\e[41m"_s;
        break;
    case QtInfoMsg:
        messageTypeSymbol = u"[I]"_s;
        messageStartColor = u"\e[44m"_s;
        break;
    }

    QString message = msg;
    message.prepend(messageTypeSymbol);
    if (!messageStartColor.isEmpty()) {
        message.prepend(messageStartColor);
        message.append(messageEndColor);
    }

    const QString dateTime = QDateTime::currentDateTime().toString(u"dd-MM-yyyy hh:mm:ss.zzz "_s);
    QString contextString = u"%1%2\t%3:%4\t%5"_s.
                            arg(QString(context.category) != u"default"_s ? u"%1 | "_s.arg(context.category) : "").
                            arg(dateTime).
                            arg(QFileInfo(context.file).fileName()).
                            arg(context.line).
                            arg(context.function);

    if (!contextStartColor.isEmpty()) {
        contextString.prepend(contextStartColor);
        contextString.append(contextEndColor);
    }

    std::cout << u"%1\n\t%2\n"_s.arg(contextString, message).toUtf8().data();
    flush(std::cout);
}


int main(int argc, char *argv[])
{
    using namespace Qt::Literals::StringLiterals;

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(u":/Timro/resources/app_icon.png"_s));
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION);

    DatabaseProvider::setDefaultDatabaseType(DatabaseProvider::DatabaseType::Sqlite);
    DirHelper::prepareWorkDirectories();
    qInstallMessageHandler(customMessageHandler);

    QtSingleApp singleApp;
    if (!singleApp.tryRun()) {
        qDebug() << "Another app is running!";
        return 1;
    }

    TimroCore core;

    core.connect(&singleApp, &QtSingleApp::anotherAppStarted, &core, &TimroCore::anotherAppStarted);

    return app.exec();
}
