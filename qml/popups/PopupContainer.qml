import QtQuick

Item {
    anchors.fill: parent

    Connections {
        target: timeController
        function onBreakStarted() {
            breakWindow.show()
        }
    }

    BreakWindow {
        id: breakWindow
    }
}
