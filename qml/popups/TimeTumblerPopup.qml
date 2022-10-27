import QtQuick

import Timro

BaseConfirmPopup {
    height: 275

    readonly property int selectedValue: timeTumbler.selectedValueInSeconds

    function show(time, text) {
        timeTumbler.reset(time)
        headerText.text = text
        open()
    }

    Text {
        id: headerText
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 5
        }
        font.pixelSize: Style.dialog.titleFontSize
        wrapMode: Text.WordWrap
        height: parent.height * 0.15
    }

    TimeTumbler {
        id: timeTumbler
        anchors.centerIn: parent
        width: parent.width * 0.45
        height: 150
    }
}
