import QtQuick

import Timro

Row {
    readonly property int selectedHour: hourListView.currentIndex
    readonly property int selectedMinute: minutesListView.currentIndex

    readonly property int selectedValueInSeconds: ((selectedHour * 60) + selectedMinute) * 60

    function reset(elapsedSeconds) {
        minutesListView.positionViewAtIndex(qmlHelper.getMinutes(elapsedSeconds), ListView.Center)
        hourListView.positionViewAtIndex(qmlHelper.getHours(elapsedSeconds), ListView.Center)
    }

    TimeNumberSpinner {
        id: hourListView
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: parent.width * 0.45
        startValue: 0
        endValue: 99
    }

    Text {
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignHCenter
        width: parent.width - (hourListView.width * 2)
        height: 1
        text: ":"
        font.pixelSize: Style.timeDisplay.editTextFontSize
    }

    TimeNumberSpinner {
        id: minutesListView
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        width: hourListView.width
        startValue: 0
        endValue: 59
    }
}
