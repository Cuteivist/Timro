import QtQuick
import QtQuick.Controls

import Timro

BasePanel {
    QtObject {
        id: priv

        property bool timeEditMode: false
    }

    TimeProgressCircle {
        id: timeCircle
        anchors.fill: parent
        currentValue: timeController.workTime
        maxValue: timeController.maxWorkTime
        editMode: timeEditDisplay.visible
        editValue: timeEditDisplay.editValue
    }

    TimeDisplay {
        id: timeDisplay
        anchors.centerIn: parent
        width: timeCircle.radius * 2
        height: width
        value: timeCircle.currentValue
        visible: !priv.timeEditMode
    }

    TimeEditDisplay {
        id: timeEditDisplay
        anchors.fill: timeDisplay
        value: timeCircle.currentValue
        visible: priv.timeEditMode
    }

    ProjectSelectionComboBox {
        anchors {
            top: parent.top
            left: parent.left
            right: timeDisplay.left
            margins: 5
            rightMargin: -10
        }
        autoAdjustPopupWidth: true
    }

    // Button column
    Column {
        anchors {
            top: parent.top
            right: parent.right
        }

        enabled: projectController.currentProjectId > 0

        ImageButton {
            width: Style.editIcon.size
            height: width
            source: "qrc:/Timro/resources/button/edit.png"
            visible: !priv.timeEditMode
            onClicked: priv.timeEditMode = true
        }

        ImageButton {
            width: Style.editIcon.size
            height: width
            source: "qrc:/Timro/resources/button/check.png"
            visible: priv.timeEditMode
            onClicked: {
                timeController.workTime = timeEditDisplay.editValue
                priv.timeEditMode = false
            }
        }

        ImageButton {
            width: Style.editIcon.size
            height: width
            source: "qrc:/Timro/resources/button/cancel.png"
            visible: priv.timeEditMode
            onClicked: {
                priv.timeEditMode = false
            }
        }

        ImageButton {
            width: Style.editIcon.size
            height: width
            source: "qrc:/Timro/resources/button/reset.png"
            visible: priv.timeEditMode
            onClicked: timeEditDisplay.reset()
        }
    }
}
