import QtQuick
import QtQuick.Controls

Item {
    id: timeBar

    Rectangle {
        anchors.fill: parent
        color: "#8EA8C1"
        opacity: 0.3
        radius: height * 0.1
    }

    PropertyAnimation { // debug
        target: priv
        property: "currentValue"
        from: 2000
        to: priv.maxValue
        duration: priv.maxValue * 1000 //60 * 1000
        loops: 1
        running: true
    }

    QtObject {
        id: priv

        property int currentValue: 0 // TODO move to cpp
        readonly property int maxValue: 8 * 60 * 60 // TODO move to cpp
        property bool timeEditMode: true
    }

    TimeProgressCircle {
        id: timeCircle
        anchors.fill: parent
        currentValue: priv.currentValue
        maxValue: priv.maxValue
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

        Button {
            width: 20
            height: 20

            onClicked: {
                priv.timeEditMode = !priv.timeEditMode
            }
        }
    }
}
