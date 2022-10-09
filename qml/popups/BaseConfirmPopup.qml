import QtQuick
import QtQuick.Controls

import "../components/controls"

Popup {
    id: popup

    signal okClicked()
    signal cancelClicked()

    modal: true
    closePolicy: Popup.NoAutoClose
    width: mainWindow.minimumWidth * 0.7
    height: mainWindow.minimumHeight * 0.4

    Row {
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        height: parent.height * 0.2
        spacing: 10

        BaseButton {
            background: Rectangle {
                color: "transparent"
                border.width: 1
            }
            textHorizontalAlignment: Text.AlignHCenter
            height: parent.height
            width: popup.width * 0.25
            text: qsTr("Ok")
            onClicked: {
                okClicked()
                close()
            }
        }

        BaseButton {
            background: Rectangle {
                color: "transparent"
                border.width: 1
            }
            text: qsTr("Cancel")
            textHorizontalAlignment: Text.AlignHCenter
            width: popup.width * 0.3
            height: parent.height
            onClicked: {
                cancelClicked()
                close()
            }
        }
    }
}
