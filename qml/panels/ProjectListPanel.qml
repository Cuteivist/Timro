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

    signal showTimePopup(int time)

    function updateTime(time) {
        selectedMaxWorkTime = time
    }

    model: projectController.model

    anchors {
        left: parent.left
        right: parent.right
    }
    height: 250

    onResetFields: {
        selectedMaxWorkTime = 8 * 60 * 60 // Default value is 8h
        nameInput.text = ""
    }

    onFillValuesFromSelected: {
        selectedMaxWorkTime = model.maxWorkTime(selectedId)
        nameInput.text = model.name(selectedId)
    }

    onConfirmAddClicked: {
        let validated = true
        // TODO validate fields and show corresponding errors
        if (nameInput.text.length == 0 || selectedMaxWorkTime == 0) {
            validated = false
        }

        if (!editMode && model.exists(nameInput.text)) {
            validated = false
        }

        if (!validated) {
            backToListMode()
            return
        }

        let result = true
        if (editMode) {
            result = model.update(selectedId, nameInput.text, selectedMaxWorkTime)
        } else {
            result = model.add(nameInput.text, selectedMaxWorkTime)
        }

        if (!result) {
            // TODO add error handling after add or update
        }

        backToListMode()
    }

    onDeleteClicked: {
        // TODO question prompt
        if (!model.remove(selectedId)) {
            // TODO error handling
        }
        selectedIndex = -1
    }

    listView.delegate: PanelListDelegate {
        id: delegate

        width: listView.width
        selected: selectedIndex === index
        onClicked: {
            if (selected) {
                selectedId = -1
                selectedIndex = -1
            } else {
                selectedId = id
                selectedIndex = index
            }
        }

        Row {
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                margins: 5
            }
            spacing: 10

            Image {
                height: 24
                width: height
                source: "qrc:/Timro/resources/selected.png"
                visible: delegate.selected
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: name
                font.pixelSize: 18
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: TimeUtils.toString(maxWorkTime)
                font.pixelSize: 18
            }
        }
    }

    editFields: [
        // TODO header (adding or editing project ABC)
        Text {
            text: qsTr("Name:")
        },
        TextField {
            id: nameInput
            leftPadding: 5
            Layout.fillWidth: true
        },
        Text {
            text: qsTr("Work time:")
        },
        Rectangle {
            color: "#A0FFFFFF"
            Layout.preferredHeight: nameInput.height
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
