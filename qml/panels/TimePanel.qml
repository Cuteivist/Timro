import QtQuick
import QtQuick.Controls

import "../components/buttons"
import "../components/time"

BasePanel {
    QtObject {
        id: priv

        property int currentValue: 0 // TODO move to cpp
        readonly property int maxValue: 8 * 60 * 60 // TODO move to cpp
        property bool timeEditMode: false
    }

    TimeProgressCircle {
        id: timeCircle
        anchors.fill: parent
        currentValue: priv.currentValue
        maxValue: priv.maxValue
        editMode: timeEditDisplay.visible
        editValue: timeEditDisplay.editValue
    }

    TimeDisplay {
        id: timeDisplay
        anchors.centerIn: parent
        width: timeCircle.radius * 2
        height: width
        value: priv.currentValue
        visible: !priv.timeEditMode
    }

    TimeEditDisplay {
        id: timeEditDisplay
        anchors.fill: timeDisplay
        value: priv.currentValue
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
            source: "qrc:/Timro/resources/button/time/edit.png"
            visible: !priv.timeEditMode
            onClicked: priv.timeEditMode = true
        }

        ImageButton {
            width: 24
            height: width
            source: "qrc:/Timro/resources/button/time/check.png"
            visible: priv.timeEditMode
            onClicked: {
                priv.currentValue = timeEditDisplay.editValue
                priv.timeEditMode = false
            }
        }

        ImageButton {
            width: 24
            height: width
            source: "qrc:/Timro/resources/button/time/cancel.png"
            visible: priv.timeEditMode
            onClicked: {
                priv.timeEditMode = false
            }
        }

        ImageButton {
            width: 24
            height: width
            source: "qrc:/Timro/resources/button/time/reset.png"
            visible: priv.timeEditMode
            onClicked: timeEditDisplay.reset()
        }
    }
}
