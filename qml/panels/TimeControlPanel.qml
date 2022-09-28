import QtQuick
import QtQuick.Layouts

import "../components/buttons"
import "../components/time"

Item {
    ColumnLayout {
        anchors.fill: parent
        Row {
            id: controlPanel
            Layout.alignment: Qt.AlignHCenter
            Layout.minimumHeight: playPauseButton.height * 0.85
            Layout.maximumHeight: playPauseButton.height * 0.85
            ControlButton {
                id: playPauseButton

                property bool running: false // TODO move to cpp

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
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
