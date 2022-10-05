import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "panels"

ApplicationWindow {
    id: mainWindow
    minimumWidth: 360
    minimumHeight: 480
    visible: true
    title: "Timro"

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
            Column {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                height: childrenRect.height
                spacing: 10

                TimePanel {
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    height: 150
                }

                ProjectPanel {
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    height: 80
                }
            }
        }
    }

    MainMenu {
        id: mainMenu
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
    }
}
