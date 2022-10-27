import QtQuick

import Timro

BasePage {
    Column {
        anchors {
            left: parent.left
            right: parent.right
        }
        height: childrenRect.height
        spacing: Style.panel.panelListSpacing

        TimePanel {
            anchors {
                left: parent.left
                right: parent.right
            }
            height: 150
        }

        WorkHistoryPanel {
            anchors {
                left: parent.left
                right: parent.right
            }
        }
    }
}
