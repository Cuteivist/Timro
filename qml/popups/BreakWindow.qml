import QtQuick

import "../components/controls"
import "../components/time"

Window {
    id: window
    flags: Qt.Dialog | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint
    modality: Qt.ApplicationModal

    x: (Screen.width - width) * 0.5
    y: Screen.height/2 - height/2

    title: qsTr("Taking a break!")

    width: 300
    height: 200

    Rectangle {
        anchors.fill: parent
        color: "#DDD4E6"
        DialogDragMouseArea {
            window: window
        }
    }

    Text {
        anchors {
            left: parent.left
            top: parent.top
            margins: 20
        }
        text: title

        font.pixelSize: 20 // TODO use style
    }

    RotatingButton {
        anchors {
            top: parent.top
            right: parent.right
        }
        source: "qrc:/Timro/resources/button/time/clock.png"
        animationRunning: true
        enabled: false
        opacity: 0.8
    }

    TimeDisplay {
        anchors {
            centerIn: parent
            verticalCenterOffset: -10
        }
        width: 100
        height: 50
        value: timeController.breakTime
        font.pixelSize: 30 // TODO use style
    }

    TextButton {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 20
        }

        text: qsTr("Finish")
        font.pixelSize: 20 // TODO use style
        onClicked: {
            timeController.start()
            window.hide()
        }
    }
}
