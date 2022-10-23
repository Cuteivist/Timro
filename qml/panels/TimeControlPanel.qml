import QtQuick
import QtQuick.Layouts

import "../components/controls"
import "../components/time"

Row {
    id: controlPanel
    height: playPauseButton.height * 0.85

    Item {
        width: breakButton.width
        height: breakButton.height
        RotatingButton {
            id: breakButton
            source: "qrc:/Timro/resources/button/time/clock.png"
            visible: timeController.workTimeRunning
            onClicked: timeController.startBreak()
        }
    }

    RotatingButton {
        id: playPauseButton
        source: timeController.workTimeRunning ? "qrc:/Timro/resources/button/time/pause.png" : "qrc:/Timro/resources/button/time/play.png"
        onClicked: {
            if (timeController.workTimeRunning) {
                timeController.pause()
            } else {
                timeController.start()
            }
        }
    }

    Item {
        width: stopButton.width
        height: stopButton.height
        RotatingButton {
            id: stopButton
            source: "qrc:/Timro/resources/button/time/stop.png"
            visible: timeController.workTimeRunning
            onClicked: timeController.reset()
        }
    }
}
