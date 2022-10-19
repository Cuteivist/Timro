import QtQuick
import QtQuick.Controls

import "../components/controls"
import "../components"

import "../utils/TimeUtils.js" as TimeUtils

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
        model: projectController.model
        onCountChanged: {
            const id = projectController.currentProjectId
            if (id < 0) {
                currentIndex = 0
                return
            }
            currentIndex = indexOfValue(projectController.currentProjectId)
        }
        textRole: "name"
        valueRole: "id"
        onActivated: projectController.currentProjectId = currentValue
    }

    AutoSizeText {
        text: {
            const maxWorkTime = timeController.maxWorkTime
            const workTime = timeController.workTime
            const percent = Math.round((workTime / maxWorkTime) * 100)
            return String("%1  [%2%]").arg(TimeUtils.toString(workTime)).arg(percent)
        }
        height: projectComboBox.height * 0.9
        anchors {
            top: projectComboBox.top
            left: projectComboBox.right
        }
    }

//    BaseComboBox {
//        id: taskComboBox
//        height: projectComboBox.height * 0.9

//        anchors {
//            left: projectComboBox.left
//            right: projectComboBox.right
//            top: projectComboBox.bottom
//        }
//        textOpacity: 0.7
//        model: ListModel {
//            ListElement { name: "TaskA" }
//            ListElement { name: "TaskB" }
//            ListElement { name: "TaskC" }
//        }
//        textRole: "name"
//    }

//    AutoSizeText {
//        text: String("%1  [%2%]").arg("02:12:15").arg("22")
//        height: projectComboBox.height * 0.9
//        opacity: taskComboBox.textOpacity
//        anchors {
//            top: taskComboBox.top
//            left: taskComboBox.right
//        }
//    }
}
