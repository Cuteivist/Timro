import QtQuick
import QtQuick.Controls

import "../panels"
import "../components"
import "../popups"

BasePage {
    Column {
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
        }
        spacing: 10

        ProjectListPanel {
            onShowTimePopup: {
                timePopup.caller = this
                let headerText
                if (editMode) {
                    headerText = qsTr("Select project '%1' max work hours").arg(model.name(selectedId))
                } else {
                    headerText = qsTr("Select project max work hours")
                }
                timePopup.show(selectedMaxWorkTime, headerText)
            }
        }
    }

    TimeTumblerPopup {
        id: timePopup

        property var caller: null

        onOkClicked: {
            if (caller === null) {
                return
            }
            caller.updateTime(selectedValue)
            caller = null
        }

        x: parent.width * 0.5 - width * 0.5
        y: mapToItem(parent, 0, mainWindow.minimumHeight * 0.5 - height).y
    }
}
