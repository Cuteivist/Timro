import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Timro

BasePanel {
    property alias editFields: editView.children
    property alias model: listViewObj.model
    property alias listView: listViewObj

    readonly property bool editViewVisible: editView.visible
    readonly property bool editMode: editView.editMode

    property int selectedId: -1
    property int selectedIndex: -1
    readonly property bool hasSelection: selectedIndex >= 0

    readonly property int contentHeight: {
        let value = topPanel.height
         if (editViewVisible) {
             value += editView.implicitHeight
             value += editView.anchors.margins * 2
         } else {
             value += listViewObj.anchors.margins * 2
             value += listViewObj.contentHeight
         }
         return value
    }
    property int maximumHeight: contentHeight

    signal resetFields()
    signal fillValuesFromSelected()

    signal confirmAddClicked()
    signal deleteClicked()

    function backToListMode() {
        editView.hide()
    }

    height: Math.min(contentHeight, maximumHeight)

    Row {
        id: topPanel
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: Style.panel.titleHeight

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
            onClicked: deleteClicked()
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
            onClicked: selectedIndex = -1
        }

        ImageButton {
            source: "qrc:/Timro/resources/button/check.png"
            visible: editViewVisible
            onClicked: confirmAddClicked()
        }
        ImageButton {
            source: "qrc:/Timro/resources/button/cancel.png"
            visible: editViewVisible
            onClicked: editView.hide()
        }
    }

    ListView {
        id: listViewObj

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
        spacing: Style.listDelegate.listSpacing
    }

    GridLayout {
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
            editView.visible = false
            editView.editMode = false
        }

        anchors {
            top: topPanel.bottom
            left: parent.left
            right: parent.right
            margins: 10
        }
        visible: false
        columns: 2
        columnSpacing: 10
    }
}
