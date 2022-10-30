import QtQuick

import Timro

Rectangle {
    id: mainMenu

    width: iconSize + 4
    color: Style.mainMenu.backgroundColor

    readonly property int iconSize: Style.mainMenu.iconSize

    signal projectListMenuClicked()
    signal homeMenuClicked()
    signal aboutMenuClicked()

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
            source: "qrc:/Timro/resources/menu/task.png"
            iconSize: mainMenu.iconSize
            active: buttonColumn.currentActiveButton === this
            onClicked: {
                buttonColumn.currentActiveButton = this
                projectListMenuClicked()
            }
        }
    }

    Column {
        id: bottomButtonColumn

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        MenuButton {
            source: "qrc:/Timro/resources/menu/about.png"
            iconSize: mainMenu.iconSize
            active: buttonColumn.currentActiveButton === this
            lineAtTheBottom: false
            onClicked: {
                buttonColumn.currentActiveButton = this
                aboutMenuClicked()
            }
        }

        MenuButton {
            source: "qrc:/Timro/resources/menu/settings.png"
            iconSize: mainMenu.iconSize
            active: buttonColumn.currentActiveButton === this
            lineAtTheBottom: false
            onClicked: {
                // TODO show settings
            }
        }
    }
}
