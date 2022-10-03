import QtQuick
import QtQuick.Controls

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

    Column {
        anchors {
            fill: parent
            leftMargin: 20
            rightMargin: 20
            topMargin: 5
        }
        spacing: 10
        TimeControlPanel {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
        }

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
            height: 100
        }
    }
}
