import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import "../components/panel"
import "../components/controls"
import "../components/delegates"

import "../utils/TimeUtils.js" as TimeUtils

ListPanel {
    id: panel

    property int selectedMaxWorkTime: 0
    property string selectedName: ""

    signal showTimePopup(int time)

    function updateTime(time) {
        selectedMaxWorkTime = time
    }

    anchors {
        left: parent.left
        right: parent.right
    }
    height: 250

    model: ListModel {
        ListElement { name: "ProjectA"; maxWorkTime: 60000 }
    }

    onResetFields: {
        selectedMaxWorkTime = 0
        selectedName = ""
    }

    onFillValuesFromSelected: {
        selectedMaxWorkTime = getSelectedItemModelValue("maxWorkTime")
        selectedName = getSelectedItemModelValue("name")
    }

    editFields: [
        // TODO header (adding or editing project ABC
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
                text: TimeUtils.toString(selectedMaxWorkTime)
            }
            MouseArea {
                anchors.fill: parent
                onClicked: showTimePopup(selectedMaxWorkTime)
            }
        },
        Item {
            Layout.fillHeight: true
        }
    ]
}
