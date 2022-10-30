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

    anchors {
        left: parent.left
        right: parent.right
    }
    model: projectController.model
    maximumHeight: 250

    onResetFields: {
        selectedMaxWorkTime = 8 * 60 * 60 // Default value is 8h
        nameInput.initialName = ""
    }

    onFillValuesFromSelected: {
        selectedMaxWorkTime = model.maxWorkTime(selectedId)
        nameInput.initialName = model.name(selectedId)
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
        height: delegateLayout.height + Style.listDelegate.margins * 2
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

        RowLayout {
            id: delegateLayout
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                margins: Style.listDelegate.margins
            }
            spacing: Style.listDelegate.spacing

            Image {
                Layout.preferredHeight: 24
                Layout.preferredWidth: 24
                source: "qrc:/Timro/resources/selected.png"
                visible: delegate.selected
            }

            Column {
                Layout.minimumHeight: height
                Text {
                    text: name
                    elide: Text.ElideRight
                    font.pixelSize: Style.listDelegate.fontSize
                }
                Text {
                    text: qsTr("Max work time: %1").arg(utils.secondsToTimeString(maxWorkTime))
                    font.pixelSize: Style.listDelegate.fontSize
                }
            }
        }
    }

    editFields: [
        Text {
            GridLayout.columnSpan: 2
            font.pixelSize: Style.global.smallFontSize
            text: editMode ? qsTr("Edit '%1'").arg(nameInput.initialName) : qsTr("Add new project")
        },
        Rectangle {
            GridLayout.columnSpan: 2
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            color: "black"
            opacity: 0.15
        },
        Text {
            text: qsTr("Name:")
            font.pixelSize: Style.global.defaultFontSize
        },
        TextField {
            id: nameInput
            property string initialName: ""
            leftPadding: 5
            Layout.fillWidth: true
            text: initialName
            font.pixelSize: Style.global.defaultFontSize
        },
        Text {
            text: qsTr("Work time:")
            font.pixelSize: Style.global.defaultFontSize
        },
        Rectangle {
            color: Style.editField.inputFieldColor
            Layout.preferredHeight: nameInput.height
            Layout.fillWidth: true
            Text {
                anchors.fill: parent
                anchors.leftMargin: 5
                text: utils.secondsToTimeString(selectedMaxWorkTime)
                font.pixelSize: Style.global.defaultFontSize
            }
            MouseArea {
                anchors.fill: parent
                onClicked: showTimePopup(selectedMaxWorkTime)
            }
        }
    ]
}
