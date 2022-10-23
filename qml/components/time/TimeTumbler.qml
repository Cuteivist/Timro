import QtQuick

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

    Item {
        width: parent.width - (hourListView.width * 2)
        height: 1
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
