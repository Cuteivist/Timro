import QtQuick
import QtQuick.Controls

import Timro

ApplicationWindow {
    id: mainWindow
    minimumWidth: 360
    minimumHeight: 480
    visible: true
    title: app.applicationName + (isDebug ? "-debug" : "")

    onVisibilityChanged: trayController.onVisibilityChanged(mainWindow.visibility)

    PageView { }

    Connections {
        target: trayController
        function onHideWindow() {
            mainWindow.hide()
        }
        function onShowWindow() {
            mainWindow.showNormal()
            mainWindow.raise()
            mainWindow.requestActivate()
        }
        function onToggleWindowVisibility() {
            if (mainWindow.visible) {
                onHideWindow()
            } else {
                onShowWindow()
            }
        }
    }

    Shortcut {
        sequence: "space"
        onActivated: {
            if (timeController.workTimeRunning) {
                timeController.pause()
            } else {
                timeController.start()
            }
        }
    }

    PopupContainer { }
}
