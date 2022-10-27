import QtQuick

import Timro

Rectangle {
    id: delegate

    default property alias defaultItem: contentItem.children
    property bool selected: false

    signal clicked()
    signal pressAndHold()

    height: Style.listDelegate.height
    radius: Style.listDelegate.radius
    color: Style.listDelegate.backgroundColor
    border.width: Style.listDelegate.borderWidth
    border.color: Style.listDelegate.borderColor

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
