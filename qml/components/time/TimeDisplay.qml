import QtQuick

import "../../utils/TimeUtils.js" as TimeUtils

Item {
    id: timeDisplay

    property int value: 0

    Text {
        anchors {
            fill: parent
            margins: 10
        }
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: TimeUtils.toString(value)
        fontSizeMode: Text.Fit
        minimumPixelSize: 15
        font.pixelSize: 50
    }
}
