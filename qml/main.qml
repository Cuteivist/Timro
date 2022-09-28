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

    TimeControlPanel {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            leftMargin: 20
            rightMargin: 20
            topMargin: 5
        }
        height: 200
        // TODO should be draggable
    }
}
