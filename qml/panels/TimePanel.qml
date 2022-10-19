import QtQuick
import QtQuick.Controls

import "../components/controls"
import "../components/time"

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

    // Button column
    Column {
        anchors {
            top: parent.top
            right: parent.right
        }

        ImageButton {
            width: 24
            height: width
            source: "qrc:/Timro/resources/button/edit.png"
            visible: !priv.timeEditMode
            onClicked: priv.timeEditMode = true
        }

        ImageButton {
            width: 24
            height: width
            source: "qrc:/Timro/resources/button/check.png"
            visible: priv.timeEditMode
            onClicked: {
                timeController.workTime = timeEditDisplay.editValue
                priv.timeEditMode = false
            }
        }

        ImageButton {
            width: 24
            height: width
            source: "qrc:/Timro/resources/button/cancel.png"
            visible: priv.timeEditMode
            onClicked: {
                priv.timeEditMode = false
            }
        }

        ImageButton {
            width: 24
            height: width
            source: "qrc:/Timro/resources/button/reset.png"
            visible: priv.timeEditMode
            onClicked: timeEditDisplay.reset()
        }
    }
}
