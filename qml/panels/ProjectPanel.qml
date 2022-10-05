import QtQuick
import QtQuick.Controls

import "../components/controls"
import "../components"

BasePanel {
    id: panel

    // TODO idea - display project icon
    BaseComboBox {
        id: projectComboBox
        width: parent.width * 0.4
        height: parent.height * 0.4
        anchors {
            top: parent.top
            left: parent.left
            margins: 5
        }
        model: ListModel { // TODO use cpp model
            ListElement { name: "ProjectA" }
            ListElement { name: "ProjectB" }
            ListElement { name: "ProjectC" }
        }
        textRole: "name"
    }

    AutoSizeText {
        text: String("%1  [%2%]").arg("05:12:15").arg("80") // TODO retrive data from model
        height: projectComboBox.height * 0.9
        anchors {
            top: projectComboBox.top
            left: projectComboBox.right
        }
    }

    BaseComboBox {
        id: taskComboBox
        height: projectComboBox.height * 0.9

        anchors {
            left: projectComboBox.left
            right: projectComboBox.right
            top: projectComboBox.bottom
        }
        textOpacity: 0.7
        model: ListModel { // TODO use cpp model
            ListElement { name: "TaskA" }
            ListElement { name: "TaskB" }
            ListElement { name: "TaskC" }
        }
        textRole: "name"
    }

    AutoSizeText {
        text: String("%1  [%2%]").arg("02:12:15").arg("22") // TODO retrive data from model
        height: projectComboBox.height * 0.9
        opacity: taskComboBox.textOpacity
        anchors {
            top: taskComboBox.top
            left: taskComboBox.right
        }
    }
}
