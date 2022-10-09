import QtQuick

import "../components/time"
import "../components"

BaseConfirmPopup {
    readonly property int selectedValue: timeTumbler.selectedValueInSeconds

    function show(time, text) {
        timeTumbler.reset(time)
        headerText.text = text
        open()
    }

    AutoSizeText {
        id: headerText
        horizontalAlignment: Qt.AlignHCenter
        width: parent.width
        height: parent.height * 0.15
    }

    TimeTumbler {
        id: timeTumbler
        anchors.centerIn: parent
        width: parent.width * 0.45
        height: parent.height * 0.6
    }
}
