import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "panels"
import "pages"

ApplicationWindow {
    id: mainWindow
    minimumWidth: 360
    minimumHeight: 480
    visible: true
    title: "Timro"

    onVisibilityChanged: trayController.onVisibilityChanged(mainWindow.visibility)

    Rectangle {
        anchors.fill: parent
        color: "#DDD4E6"
    }

    ColumnLayout {
        anchors {
            top: parent.top
            left: mainMenu.right
            right: parent.right
            bottom: parent.bottom
            leftMargin: 10
            rightMargin: 10
            topMargin: 5
        }

        TimeControlPanel {
            Layout.alignment: Qt.AlignHCenter
        }

        Flickable {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            contentHeight: stackView.currentItem.height
            bottomMargin: 10
            boundsBehavior: Flickable.StopAtBounds
            ScrollIndicator.vertical: ScrollIndicator { }

            StackView {
                id: stackView
                anchors.fill: parent
                initialItem: HomePage { }
            }
        }
    }

    Component {
        id: projectList
        ProjectListPage { }
    }

    MainMenu {
        id: mainMenu
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        onHomeMenuClicked: {
            if (stackView.depth > 1)
                stackView.pop()
        }

        onProjectListMenuClicked: {
            if (stackView.depth === 1)
                stackView.push(projectList)
        }
    }

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
}
