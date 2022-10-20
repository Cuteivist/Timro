#ifndef TRAYCONTROLLER_H
#define TRAYCONTROLLER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QWindow>
#include <QMenu>

class TrayController : public QObject
{
    Q_OBJECT
public:
    explicit TrayController(QObject *parent = nullptr);

    bool isTrayAvailable() const;

    void initProjectMenuGroup(const QHash<int, QString> &projects);

public slots:
    void onVisibilityChanged(QWindow::Visibility visibility);
    void onTrayActivated(QSystemTrayIcon::ActivationReason activationReason);
    void onWorkTimeChanged(const int workTime);

    // Project group slots
    void onCurrentProjectChanged(const int projectId);
    void onProjectAdded(const int projectId, const QString &name);
    void onProjectRemoved(const int projectId);
    void onProjectRenamed(const int projectId, const QString &name);

private slots:
    void onRunningChanged(const bool running);

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
    void runningChanged(const bool running) const;

private:
    bool mIsTrayAvailable;
    QSystemTrayIcon mTrayIcon;
    QScopedPointer<QMenu> mTrayMenu;
    QActionGroup *mProjectGroup {};
    QMenu *mProjectMenu {};

    void init();
    void initMenu();

    void updateToolTip();
    void updateTrayIcon();

    void quit();
};

#endif // TRAYCONTROLLER_H
