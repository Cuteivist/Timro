import QtQuick

import "../components/controls"

Rectangle {
    id: mainMenu

    width: 36
    color: "#1981A1"

    readonly property int iconSize: 32

    signal projectListMenuClicked()
    signal homeMenuClicked()

    Column {
        id: buttonColumn

        property var currentActiveButton: homeButton

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        MenuButton {
            source: "qrc:/Timro/resources/menu/menu_show.png"
            iconSize: mainMenu.iconSize
            onClicked: {
                // TODO implement extending menu
            }
        }

        MenuButton {
            id: homeButton
            source: "qrc:/Timro/resources/menu/home.png"
            iconSize: mainMenu.iconSize
            active: buttonColumn.currentActiveButton === this
            onClicked: {
                buttonColumn.currentActiveButton = this
                homeMenuClicked()
            }
        }

        MenuButton {
            id: projectListButton
            source: "qrc:/Timro/resources/menu/task.png"
            iconSize: mainMenu.iconSize
            active: buttonColumn.currentActiveButton === this
            onClicked: {
                buttonColumn.currentActiveButton = this
                projectListMenuClicked()
            }
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
