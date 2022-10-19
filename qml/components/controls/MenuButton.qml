import QtQuick
import QtQuick.Layouts

Item {
    id: menuButton
    property alias source: button.source
    property alias iconSize: button.iconSize
    property bool lineAtTheBottom: true

    property bool active: false

    signal clicked()

    width: parent.width
    height: parent.width

    Rectangle {
        anchors.fill: parent
        color: active ? "white" : "transparent"
        opacity: 0.3
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        rotation: lineAtTheBottom ? 0 : 180

        ImageButton {
            id: button
            Layout.fillHeight: true
            Layout.fillWidth: true
            iconSize: mainMenu.iconSize
            width: parent.width
            height: width
            rotation: parent.rotation
            onClicked: menuButton.clicked()
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.maximumHeight: 1
            Layout.minimumHeight: 1
            color: "white"
        }
    }
}
