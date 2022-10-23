import QtQuick

BaseButton {
    textHorizontalAlignment: Qt.AlignHCenter
    textVerticalAlignment: Qt.AlignVCenter

    width: contentItem.paintedWidth * 1.2
    height: contentItem.paintedHeight * 1.2

    background: Rectangle {
        color: "transparent"
        border.width: 1
    }
}
