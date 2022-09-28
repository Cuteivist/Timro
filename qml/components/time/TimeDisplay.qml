import QtQuick

Item {
    id: timeDisplay

    property int value: 0

    function formatTime(timeSecs) { // TODO move to cpp
        var hours, mins, secs
        secs = timeSecs%60
        mins = (Math.floor(timeSecs/60))%60
        hours = Math.floor( (Math.floor(timeSecs/60))/60 )

        var hoursStr, minsStr, secsStr
        secsStr = secs > 9 ? secs : '0' + secs
        minsStr = mins > 9 ? mins : '0' + mins
        hoursStr = hours > 9 ? hours : '0' + hours

        return hoursStr + ':' + minsStr + ':' + secsStr
    }

    Text {
        anchors {
            fill: parent
            margins: 10
        }
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: formatTime(value)
        fontSizeMode: Text.Fit
        minimumPixelSize: 15
        font.pixelSize: 50
    }
}
