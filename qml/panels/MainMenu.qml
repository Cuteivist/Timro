import QtQuick

import "../components/controls"

Rectangle {
    id: mainMenu

    width: 36
    color: "#1981A1"

    readonly property int iconSize: 32

    Column {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        MenuButton {
            source: "qrc:/Timro/resources/menu/menu_show.png"
            iconSize: mainMenu.iconSize
            onClicked: {
                // todo extend menu
            }
        }

        MenuButton {
            source: "qrc:/Timro/resources/menu/task.png"
            iconSize: mainMenu.iconSize
        }
    }

    MenuButton {
        anchors {
            bottom: parent.bottom
        }
        lineAtTheBottom: false
        source: "qrc:/Timro/resources/menu/settings.png"
    }
}
