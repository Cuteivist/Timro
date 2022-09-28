import QtQuick

Item {
    id: timeDisplay

    readonly property int editValue: ((hourListView.currentIndex * 60) + minutesListView.currentIndex) * 60

    property int value: 0

    onVisibleChanged: {
        if (!visible) {
            return
        }
        const fullMinutes = Math.floor(value / 60)
        const mins = (fullMinutes) % 60
        minutesListView.positionViewAtIndex(mins, ListView.Center)
        const hours = Math.floor(fullMinutes / 60)
        hourListView.positionViewAtIndex(hours, ListView.Center)
    }

    Row {
        anchors.centerIn: parent
        width: parent.width * 0.7
        height: parent.height
        TimeNumberSpinner {
            id: hourListView
            anchors {
                top: parent.top
                bottom: parent.bottom
            }
            width: parent.width * 0.45
            startValue: 0
            endValue: 99

            Component.onCompleted: { // debug
                hourListView.positionViewAtIndex(7, ListView.Center)
                minutesListView.positionViewAtIndex(30, ListView.Center)
            }
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - (hourListView.width * 2)
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
            text : ":"
            minimumPixelSize: 10
            font.pixelSize: 50
            fontSizeMode: Text.HorizontalFit
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
}
