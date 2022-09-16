import QtQuick

import "../components/buttons"
import "../components/time"

Item {
    Column {
        spacing: 10
        anchors.fill: parent
        Row {
            id: controlPanel
            anchors.horizontalCenter: parent.horizontalCenter
            ControlButton {
                id: playPauseButton

                property bool running: false

                source: playPauseButton.running ? "qrc:/Timro/resources/button/pause.png" : "qrc:/Timro/resources/button/play.png"
                onClicked: {
                    // TODO add
                    running = !running
                }
            }

            Item {
                width: stopButton.width
                height: stopButton.height
                ControlButton {
                    id: stopButton
                    source: "qrc:/Timro/resources/button/stop.png"
                    visible: playPauseButton.running
                    onClicked: {
                        // TODO add reset functionality
                    }
                }
            }
        }

        TimeBar {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 100
        }
    }
}
