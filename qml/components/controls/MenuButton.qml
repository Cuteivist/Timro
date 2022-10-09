import QtQuick
import QtQuick.Layouts

Item {
    id: menuButton
    property alias source: button.source
    property alias iconSize: button.iconSize
    property bool lineAtTheBottom: true

    signal clicked()

    width: parent.width
    height: parent.width

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
            // TODO add shader to change color to white
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.maximumHeight: 1
            Layout.minimumHeight: 1
            color: "white"
        }
    }
}
