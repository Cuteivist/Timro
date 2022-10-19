import QtQuick
import QtQuick.Layouts

import "../components/controls"
import "../components/time"

Row {
    id: controlPanel
    height: playPauseButton.height * 0.85
    RotatingButton {
        id: playPauseButton
        source: timeController.running ? "qrc:/Timro/resources/button/time/pause.png" : "qrc:/Timro/resources/button/time/play.png"
        onClicked: {
            if (timeController.running) {
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
            visible: timeController.running
            onClicked: timeController.reset()
        }
    }
}
