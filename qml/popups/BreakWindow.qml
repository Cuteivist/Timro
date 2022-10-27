import QtQuick

import Timro

Window {
    id: window
    flags: Qt.Dialog | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint
    modality: Qt.ApplicationModal

    x: (Screen.width - width) * 0.5
    y: (Screen.height - height) * 0.5

    title: qsTr("Taking a break!")

    width: 300
    height: 200

    Rectangle {
        anchors.fill: parent
        color: Style.dialog.backgroundColor
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

        font.pixelSize: Style.dialog.titleFontSize
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
        font.pixelSize: Style.dialog.contentItemFontSize
    }

    TextButton {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 20
        }

        text: qsTr("Finish")
        font.pixelSize: Style.dialog.buttonFontSize
        onClicked: {
            timeController.start()
            window.hide()
        }
    }
}
