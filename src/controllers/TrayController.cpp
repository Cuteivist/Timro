#include "TrayController.h"

#include <QActionGroup>
#include <QApplication>
#include <QPainter>

using namespace Qt::Literals::StringLiterals;

namespace {
const auto PROJECT_ID_PROPERTY = QLatin1StringView("project_id");
}

TrayController::TrayController(QObject *parent)
    : QObject(parent)
{
    mIsTrayAvailable = QSystemTrayIcon::isSystemTrayAvailable();
    if (mIsTrayAvailable) {
        init();
    }
}

bool TrayController::isTrayAvailable() const
{
    return mIsTrayAvailable;
}

void TrayController::initProjectMenuGroup(const QHash<int, QString> &projects)
{
    for (auto [id, name] : projects.asKeyValueRange()) {
        onProjectAdded(id, name);
    }
}

void TrayController::onVisibilityChanged(QWindow::Visibility visibility)
{
    switch(visibility) {
    case QWindow::Minimized:
        emit hideWindow();
        break;
    default:
        break;
    }
}

void TrayController::onTrayActivated(QSystemTrayIcon::ActivationReason activationReason)
{
    if (activationReason == QSystemTrayIcon::Trigger) {
        emit toggleWindowVisibility();
    }
}

void TrayController::onWorkTimeChanged(const int workTime)
{
    if (!mShowingTimeInTrayIcon) {
        return;
    }

    QPixmap pixmap(30,30);
    pixmap.fill(QColor(144, 238, 144));

    QPainter painter(&pixmap);

    const int totalMinutes = qFloor(workTime / 60);
    const QString minutes = QString::number(totalMinutes % 60);
    const QString hours = QString::number(qFloor(totalMinutes / 60));

    painter.drawText(pixmap.rect(), Qt::AlignCenter, u"%1:%2"_s.arg(hours, minutes));
    mTrayIcon.setIcon(pixmap);
}

void TrayController::onCurrentProjectChanged(const int projectId)
{
    for (auto action : mProjectGroup->actions()) {
        if (action->property(PROJECT_ID_PROPERTY.data()).toInt() == projectId) {
            action->setChecked(true);
        } else {
            action->setChecked(false);
        }
    }
}

void TrayController::onProjectAdded(const int projectId, const QString &name)
{
    auto action = mProjectMenu->addAction(name);
    action->setCheckable(true);
    action->setProperty(PROJECT_ID_PROPERTY.data(), projectId);
    action->setActionGroup(mProjectGroup);
    connect(action, &QAction::toggled, this, [this, action](const bool checked) {
        if (!checked) {
            return;
        }
        emit currentProjectChanged(action->property(PROJECT_ID_PROPERTY.data()).toInt());
    });
    mProjectMenu->setEnabled(true);
}

void TrayController::onProjectRemoved(const int projectId)
{
    for (auto action : mProjectGroup->actions()) {
        if (action->property(PROJECT_ID_PROPERTY.data()).toInt() == projectId) {
            mProjectGroup->removeAction(action);
            mProjectMenu->removeAction(action);
            action->deleteLater();
            mProjectMenu->setEnabled(!mProjectGroup->actions().isEmpty());
            return;
        }
    }
}

void TrayController::onProjectRenamed(const int projectId, const QString &name)
{
    for (auto action : mProjectGroup->actions()) {
        if (action->property(PROJECT_ID_PROPERTY.data()).toInt() == projectId) {
            action->setText(name);
            return;
        }
    }
}

void TrayController::onWorkTimeRunningChanged(const bool running)
{
    mShowingTimeInTrayIcon = running;
    if (!running) {
        mTrayIcon.setIcon(QApplication::windowIcon());
    }
}

void TrayController::init()
{
    QApplication* app = qobject_cast<QApplication*>(QApplication::instance());
    if (app) {
        app->setQuitOnLastWindowClosed(false);
    }

    mTrayIcon.setIcon(QApplication::windowIcon());

    connect(&mTrayIcon, &QSystemTrayIcon::activated, this, &TrayController::onTrayActivated);
    connect(this, &TrayController::workTimeRunningChanged, this, &TrayController::onWorkTimeRunningChanged);

    initMenu();

    mTrayIcon.show();
}

void TrayController::initMenu()
{
    mTrayMenu.reset(new QMenu(QApplication::applicationName()));

    auto appAction = mTrayMenu->addAction(QApplication::windowIcon(), QApplication::applicationName());
    connect(appAction, &QAction::triggered, this, &TrayController::showWindow);

    mTrayMenu->addSeparator();

    auto startPauseAction = mTrayMenu->addAction(tr("Start"));
    connect(startPauseAction, &QAction::triggered, this, &TrayController::toggleStartPause);
    connect(this, &TrayController::workTimeRunningChanged, this, [startPauseAction](const bool running) {
        startPauseAction->setText(running ? tr("Pause") : tr("Start"));
    });

    auto breakAction = mTrayMenu->addAction(tr("Start break"));
    connect(breakAction, &QAction::triggered, this, &TrayController::startBreak);
    connect(this, &TrayController::workTimeRunningChanged, breakAction, &QAction::setEnabled);
    connect(this, &TrayController::breakStarted, this, [startPauseAction, breakAction] {
        startPauseAction->setEnabled(false);
        breakAction->setEnabled(false);
    });
    connect(this, &TrayController::breakFinished, this, [startPauseAction, breakAction] {
        startPauseAction->setEnabled(true);
        breakAction->setEnabled(true);
    });

    mTrayMenu->addSeparator();

    mProjectMenu = mTrayMenu->addMenu(tr("Projects"));
    mProjectMenu->setEnabled(false);
    mProjectGroup = new QActionGroup(mProjectMenu);

    mTrayMenu->addSeparator();

    auto quitAction = mTrayMenu->addAction(tr("Quit"));
    connect(quitAction, &QAction::triggered, this, &TrayController::quit);

    mTrayIcon.setContextMenu(mTrayMenu.data());
}

void TrayController::updateToolTip()
{
    static const QString tooltipTemplate = tr("");
    mTrayIcon.setToolTip(tooltipTemplate);
}

void TrayController::quit()
{
    emit beforeQuit();
    QApplication::quit();
}
