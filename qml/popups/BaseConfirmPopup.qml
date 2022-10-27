import QtQuick
import QtQuick.Controls

import Timro

Popup {
    id: popup

    signal okClicked()
    signal cancelClicked()

    modal: true
    closePolicy: Popup.NoAutoClose
    width: 250
    height: 200

    background: Rectangle {
        color: Style.dialog.backgroundColor
    }

    Row {
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        spacing: Style.dialog.buttonRowSpacing

        TextButton {
            id: okButton
            text: qsTr("Ok")
            width: Math.max(okButton.contentItem.paintedWidth, cancelButton.contentItem.paintedWidth) * 1.2
            font.pixelSize: Style.dialog.buttonFontSize
            onClicked: {
                okClicked()
                close()
            }
        }

        TextButton {
            id: cancelButton
            text: qsTr("Cancel")
            width: okButton.width
            font.pixelSize: Style.dialog.buttonFontSize
            onClicked: {
                cancelClicked()
                close()
            }
        }
    }
}
