import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Timro

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
        // TODO add validate fields and show corresponding errors
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
        // TODO show question prompt
        if (!model.remove(selectedId)) {
            // TODO add error handling
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
                font.pixelSize: Style.listDelegate.fontSize
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: qmlHelper.secondsToTimeString(maxWorkTime)
                font.pixelSize: Style.listDelegate.fontSize
            }
        }
    }

    editFields: [
        // TODO implement header (adding or editing project ABC)
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
            color: Style.editField.inputFieldColor
            Layout.preferredHeight: nameInput.height
            Layout.fillWidth: true
            Text {
                anchors.fill: parent
                anchors.leftMargin: 5
                text: qmlHelper.secondsToTimeString(selectedMaxWorkTime)
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
