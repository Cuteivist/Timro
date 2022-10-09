import QtQuick

import "../panels"

BasePage {
    Column {
        anchors {
            left: parent.left
            right: parent.right
        }
        height: childrenRect.height
        spacing: 10

        TimePanel {
            anchors {
                left: parent.left
                right: parent.right
            }
            height: 150
        }

        ProjectPanel {
            anchors {
                left: parent.left
                right: parent.right
            }
            height: 80
        }
    }
}
