import QtQuick

import Timro

Text {
    id: timeDisplay

    property int value: 0

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    text: qmlHelper.secondsToTimeString(value)
    font.pixelSize: Style.timeDisplay.textFontSize
}
