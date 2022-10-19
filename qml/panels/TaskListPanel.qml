import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import "../components/panel"
import "../components/controls"
import "../components/delegates"

ListPanel {

    signal showTimePopup(int time)

    anchors {
        left: parent.left
        right: parent.right
    }
    height: 250

    model: ListModel {
        ListElement { name: "TaskA"; maxWorkTime: 6000 }
    }

    editFields: [
        Text {
            text: qsTr("Name:")
        },
        TextField {
            id: textField
            leftPadding: 5
            Layout.fillWidth: true
        },
        Text {
            text: qsTr("Work time:")
        },
        Rectangle {
            color: "#A0FFFFFF"
            Layout.preferredHeight: textField.height
            Layout.fillWidth: true
            Text {
                anchors.fill: parent
                anchors.leftMargin: 5
                text: "05:20"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {

                }
            }
        },
        Item {
            Layout.fillHeight: true
        }
    ]
}
