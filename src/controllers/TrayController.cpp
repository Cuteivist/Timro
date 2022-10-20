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
    if (!mTrayIcon.icon().isNull()) {
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

void TrayController::onRunningChanged(const bool running)
{
    if (running) {
        mTrayIcon.setIcon(QIcon());
        return;
    }

    mTrayIcon.setIcon(QApplication::windowIcon());
}

void TrayController::init()
{
    QApplication* app = qobject_cast<QApplication*>(QApplication::instance());
    if (app) {
        app->setQuitOnLastWindowClosed(false);
    }

    mTrayIcon.setIcon(QApplication::windowIcon());

    connect(&mTrayIcon, &QSystemTrayIcon::activated, this, &TrayController::onTrayActivated);
    connect(this, &TrayController::runningChanged, this, &TrayController::onRunningChanged);

    // TODO add connects to update tooltip

    initMenu();

    mTrayIcon.show();
}

void TrayController::initMenu()
{
    mTrayMenu.reset(new QMenu(QApplication::applicationName()));

    auto action = mTrayMenu->addAction(QApplication::windowIcon(), QApplication::applicationName());
    connect(action, &QAction::triggered, this, &TrayController::showWindow);

    mTrayMenu->addSeparator();

    action = mTrayMenu->addAction(tr("Start"));
    connect(action, &QAction::triggered, this, &TrayController::toggleStartPause);
    connect(this, &TrayController::runningChanged, this, [action](const bool running) {
        action->setText(running ? tr("Pause") : tr("Start"));
    });

    action = mTrayMenu->addAction(tr("Start break"));
    connect(action, &QAction::triggered, this, &TrayController::startBreak);
    connect(this, &TrayController::runningChanged, action, &QAction::setEnabled);
    // TODO disable option if break is running

    mTrayMenu->addSeparator();

    mProjectMenu = mTrayMenu->addMenu(tr("Projects"));
    mProjectMenu->setEnabled(false);
    mProjectGroup = new QActionGroup(mProjectMenu);

    mTrayMenu->addSeparator();

    action = mTrayMenu->addAction(tr("Quit"));
    connect(action, &QAction::triggered, this, &TrayController::quit);

    mTrayIcon.setContextMenu(mTrayMenu.data());
}

void TrayController::updateToolTip()
{
    // TODO fill tooltip string
    static const QString tooltipTemplate = tr("");

    mTrayIcon.setToolTip(tooltipTemplate);
}

void TrayController::quit()
{
    emit beforeQuit();
    QApplication::quit();
}
