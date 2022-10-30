import QtQuick

import Timro

Text {
    id: timeDisplay

    property int value: 0

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    text: utils.secondsToTimeString(value)
    font.pixelSize: Style.timeDisplay.textFontSize
}
