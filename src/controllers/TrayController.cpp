#include "TrayController.h"

#include "helpers/Utils.h"

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
    if (!validForRedraw(mTooltipInfo.workTime, workTime)) {
        return;
    }
    mTooltipInfo.workTime = workTime;
    updateTrayIcon();
    updateToolTip();
}

void TrayController::onSessionWorkTimeChanged(const int workTime)
{
    if (workTime <= 0) {
        mTooltipInfo.sessionWorkTime = -1;
        updateToolTip();
        return;
    }
    if (!validForRedraw(mTooltipInfo.sessionWorkTime, workTime)) {
        return;
    }
    mTooltipInfo.sessionWorkTime = workTime;
    updateToolTip();
}

void TrayController::onCurrentProjectChanged(const int projectId)
{
    for (auto action : mProjectGroup->actions()) {
        if (action->property(PROJECT_ID_PROPERTY.data()).toInt() == projectId) {
            action->setChecked(true);
            mTooltipInfo.projectName = action->text();
            updateToolTip();
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
            const bool projectsAvailable = !mProjectGroup->actions().isEmpty();
            mProjectMenu->setEnabled(projectsAvailable);
            if (!projectsAvailable) {
                mTooltipInfo.projectName.clear();
                mTooltipInfo.workTime = 0;
                updateToolTip();
            }
            return;
        }
    }
}

void TrayController::onProjectRenamed(const int projectId, const QString &name)
{
    for (auto action : mProjectGroup->actions()) {
        if (action->property(PROJECT_ID_PROPERTY.data()).toInt() == projectId) {
            action->setText(name);
            if (action->isChecked()) {
                // Rename current project
                mTooltipInfo.projectName = action->text();
                updateToolTip();
            }
            return;
        }
    }
}

void TrayController::onWorkTimeRunningChanged(const bool running)
{
    mShowingTimeInTrayIcon = running;
    updateTrayIcon(true);
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

    connect(this, &TrayController::breakStarted, this, [this] {
        mTooltipInfo.lastBreakEndTime = QDateTime();
        updateToolTip();
    });
    connect(this, &TrayController::breakFinished, this, [this] {
        mTooltipInfo.lastBreakEndTime = QDateTime::currentDateTimeUtc();
        updateToolTip();
    });


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
    QStringList tooltipInfo;
    if (!mTooltipInfo.projectName.isEmpty()) {
        tooltipInfo << tr("CURRENT PROJECT") << mTooltipInfo.projectName;
    }
    tooltipInfo << tr("WORK TIME") << Utils::secondsToTimeString(mTooltipInfo.workTime, false);
    if (mTooltipInfo.sessionWorkTime >= 0) {
        tooltipInfo << tr("SESSION WORK TIME") << Utils::secondsToTimeString(mTooltipInfo.sessionWorkTime, false);
    }
    if (mTooltipInfo.lastBreakEndTime.isValid()) {
        tooltipInfo << tr("TIME SINCE LAST BREAK");
        const int secondsSinceLastBreak = mTooltipInfo.lastBreakEndTime.msecsTo(QDateTime::currentDateTimeUtc()) / 1000;
        tooltipInfo << Utils::secondsToTimeString(secondsSinceLastBreak, false);
    }
    mTrayIcon.setToolTip(tooltipInfo.join('\n'));
}

void TrayController::updateTrayIcon(const bool force)
{
    if (!mShowingTimeInTrayIcon && !force) {
        return;
    }

    QPixmap pixmap(30,30);
    pixmap.fill(QColor(144, 238, 144));

    QPainter painter(&pixmap);

    const int totalMinutes = qFloor(mTooltipInfo.workTime / 60);
    const QString minutes = QString::number(totalMinutes % 60);
    const QString hours = QString::number(qFloor(totalMinutes / 60));

    painter.drawText(pixmap.rect(), Qt::AlignCenter, u"%1:%2"_s.arg(hours, minutes));
    mTrayIcon.setIcon(pixmap);
}

bool TrayController::validForRedraw(const int lastDrawTimeSecs, const int currentTimeSecs) const
{
    if (lastDrawTimeSecs <= 0) {
        return true;
    }
    const int timeDiff = currentTimeSecs - lastDrawTimeSecs;
    static const int refreshTimeInSeconds = 60;
    if (timeDiff >= refreshTimeInSeconds || timeDiff < 0) {
        return true;
    }
    // If minute didn't change since last redraw, skip update
    // e.g. Last paint was on 00:22:33 and current time is 00:22:55
    return Utils::getMinutes(currentTimeSecs) != Utils::getMinutes(lastDrawTimeSecs);
}

void TrayController::quit()
{
    emit beforeQuit();
    QApplication::quit();
}
