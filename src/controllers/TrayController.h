#ifndef TRAYCONTROLLER_H
#define TRAYCONTROLLER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QWindow>
#include <QDateTime>
#include <QMenu>

class TrayController : public QObject
{
    Q_OBJECT
public:
    explicit TrayController(QObject *parent = nullptr);
    Q_DISABLE_COPY(TrayController)

    bool isTrayAvailable() const;

    void initProjectMenuGroup(const QHash<int, QString> &projects);

public slots:
    void onVisibilityChanged(QWindow::Visibility visibility);
    void onTrayActivated(QSystemTrayIcon::ActivationReason activationReason);
    void onWorkTimeChanged(const int workTime);
    void onSessionWorkTimeChanged(const int workTime);

    // Project group slots
    void onCurrentProjectChanged(const int projectId);
    void onProjectAdded(const int projectId, const QString &name);
    void onProjectRemoved(const int projectId);
    void onProjectRenamed(const int projectId, const QString &name);

private slots:
    void onWorkTimeRunningChanged(const bool running);
    void updateToolTip();

signals:
    // outgoing
    void hideWindow() const;
    void showWindow() const;
    void toggleWindowVisibility() const;
    void toggleStartPause() const;
    void startBreak() const;
    void currentProjectChanged(const int projectId) const;
    void beforeQuit() const;

    // incoming
    void workTimeRunningChanged(const bool running) const;
    void breakStarted() const;
    void breakFinished() const;

private:
    struct TooltipInfo {
        QString projectName;
        int workTime {0}, sessionWorkTime {-1};
        QDateTime lastBreakEndTime;
    };
    TooltipInfo mTooltipInfo;
    bool mIsTrayAvailable;
    bool mShowingTimeInTrayIcon = false;
    QSystemTrayIcon mTrayIcon;
    QScopedPointer<QMenu> mTrayMenu;
    QActionGroup *mProjectGroup {};
    QMenu *mProjectMenu {};

    void init();
    void initMenu();

    void updateTrayIcon(const bool force = false);

    bool validForRedraw(const int lastDrawTimeSecs, const int currentTimeSecs) const;

    void quit();
};

#endif // TRAYCONTROLLER_H
