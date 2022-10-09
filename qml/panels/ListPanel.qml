import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import "../components/panel"
import "../components/controls"
import "../components/delegates"

import "../utils/ModelUtils.js" as ModelUtils

BasePanel {

    property alias editFields: grid.children
    property alias model: listView.model

    readonly property bool editViewVisible: editView.visible
    readonly property bool editMode: editView.editMode

    readonly property alias selectedIndex: listView.selectedIndex
    readonly property bool hasSelection: selectedIndex >= 0

    signal resetFields()
    signal fillValuesFromSelected()

    function getSelectedItemModelValue(role) {
        if (!hasSelection) {
            return ""
        }
        return ModelUtils.getValue(model, selectedIndex, role)
    }

    Row {
        id: topPanel
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: parent.height * 0.1

        PanelTitle {
            height: parent.height
            text: qsTr("Projects")
        }

        Item {
            height: parent.height
            width: 10
        }

        ImageButton {
            source: "qrc:/Timro/resources/button/add.png"
            visible: !editViewVisible
            onClicked: editView.show()
        }

        ImageButton {
            source: "qrc:/Timro/resources/button/trash.png"
            enabled: hasSelection
            visible: !editViewVisible
            onClicked: {
                // TODO delete item
            }
        }

        ImageButton {
            source: "qrc:/Timro/resources/button/edit.png"
            enabled: hasSelection
            visible: !editViewVisible
            onClicked: editView.showEditMode()
        }

        // To be implemented
//        ImageButton {
//            source: "qrc:/Timro/resources/button/select_all.png"
//            visible: !editViewVisible
//            onClicked: {

//            }
//        }

        ImageButton {
            source: "qrc:/Timro/resources/button/reset.png"
            enabled: hasSelection
            visible: !editViewVisible
            onClicked: listView.selectedIndex = -1
        }

        ImageButton {
            source: "qrc:/Timro/resources/button/check.png"
            visible: editViewVisible
            onClicked: {
                // TODO update values
            }
        }
        ImageButton {
            source: "qrc:/Timro/resources/button/cancel.png"
            visible: editViewVisible
            onClicked: editView.hide()
        }
    }

    ListView {
        id: listView

        property int selectedIndex: -1

        anchors {
            top: topPanel.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
        visible: !editViewVisible
        clip: true
        boundsBehavior: ListView.StopAtBounds

        delegate: PanelListDelegate {
            id: delegate

            selected: selectedIndex === index
            onPressAndHold: {
                if (selected) {
                    listView.selectedIndex = -1
                } else {
                    listView.selectedIndex = index
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
                    text: maxWorkTime
                    font.pixelSize: 18
                }
            }
        }
    }

    Item {
        id: editView

        property bool editMode: false

        function show() {
            resetFields()
            editMode = false
            visible = true
        }

        function showEditMode() {
            fillValuesFromSelected()
            editMode = true
            visible = true
        }

        function hide() {
            visible = false
            editMode = false
        }

        anchors.fill: listView
        visible: false

        GridLayout {
            id: grid
            anchors.fill: parent
            columns: 2
            columnSpacing: 10
        }
    }
}
