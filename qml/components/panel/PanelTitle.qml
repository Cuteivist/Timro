import QtQuick

import Timro

Item {
    property alias text: title.text
    property alias leftPadding: title.leftPadding

    property color frameColor: "#0F2C40"

    height: Style.panel.titleHeight
    width: title.paintedWidth + title.leftPadding + Style.panel.padding

    Text {
        id: title
        anchors.fill: parent
        leftPadding: Style.panel.padding * 2
        font.pixelSize: Style.panel.titleFontSize
    }

    Rectangle {
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        height: 1
        color: frameColor
    }

    Rectangle {
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        width: 1
        color: frameColor
    }
}
