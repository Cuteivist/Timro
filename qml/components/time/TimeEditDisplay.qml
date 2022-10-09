import QtQuick

Item {
    id: timeDisplay

    readonly property int editValue: tumbler.selectedValueInSeconds

    property int value: 0

    onVisibleChanged: {
        if (!visible) {
            return
        }
        reset()
    }

    function reset() {
        tumbler.reset(value)
    }

    TimeTumbler {
        id: tumbler
        anchors.centerIn: parent
        width: parent.width * 0.7
        height: parent.height
    }
}
