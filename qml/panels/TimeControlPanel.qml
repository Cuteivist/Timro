import QtQuick
import QtQuick.Layouts

import "../components/buttons"
import "../components/time"

Row {
    id: controlPanel
    height: playPauseButton.height * 0.85
    RotatingButton {
        id: playPauseButton

        property bool running: false // TODO move to cpp

        source: playPauseButton.running ? "qrc:/Timro/resources/button/time/pause.png" : "qrc:/Timro/resources/button/time/play.png"
        onClicked: {
            // TODO add
            running = !running
        }
    }

    Item {
        width: stopButton.width
        height: stopButton.height
        RotatingButton {
            id: stopButton
            source: "qrc:/Timro/resources/button/time/stop.png"
            visible: playPauseButton.running
            onClicked: {
                playPauseButton.running = false
                // TODO add reset functionality
            }
        }
    }
}
