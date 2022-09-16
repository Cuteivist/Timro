import QtQuick
import QtQuick.Controls

import "panels"

ApplicationWindow {
    id: mainWindow
    minimumWidth: 360
    minimumHeight: 480
    visible: true
    title: qsTr("Timro")

    Rectangle {
        anchors.fill: parent
        color: "#DDD4E6"
    }

    TimeControlPanel {
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }
}
