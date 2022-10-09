import QtQuick

import ".."

Item {
    property alias text: title.text
    property alias leftPadding: title.leftPadding

    property color frameColor: "#0F2C40"

    height: parent.height * 0.1
    width: title.paintedWidth + title.leftPadding + 5

    AutoSizeText {
        id: title
        anchors.fill: parent
        fontSizeMode: Text.VerticalFit
        leftPadding: 10
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
