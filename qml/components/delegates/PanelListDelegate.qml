import QtQuick 2.15

Rectangle {
    id: delegate

    default property alias defaultItem: contentItem.children
    property bool selected: false

    signal clicked()
    signal pressAndHold()

    height: 40
    radius: 5
    color: "#80FFFFFF"
    border.width: 1
    border.color: "black"

    Item {
        id: contentItem
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        onPressAndHold: delegate.pressAndHold()
        onClicked: delegate.clicked()
    }
}
