import QtQuick
import QtQuick.Layouts

import Timro

Rectangle {
    id: collapsableSection

    property alias model: sectionListView.model
    property alias delegate: sectionListView.delegate
    property alias title: titleText.text

    property bool collapsed: true

    function collapse() {
        if (collapsed)
            return
        collapsed = true
    }

    function expand() {
        if (!collapsed)
            return
        collapsed = false
    }

    color: Style.collapsableSection.backgroundColor
    radius: Style.collapsableSection.radius

    Row {
        id: sectionTitle
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: Style.collapsableSection.padding
        }
        height: childrenRect.height + Style.collapsableSection.padding
        spacing: Style.collapsableSection.spacing

        Image {
            source: Style.collapsableSection.icon
            rotation: collapsableSection.collapsed ? 0 : 180
            width: Style.collapsableSection.iconSize
            height: width
        }

        Text {
            id: titleText
            font.pixelSize: Style.collapsableSection.titleFontSize
        }
    }

    ListView {
        id: sectionListView
        anchors {
            top: sectionTitle.bottom
            left: parent.left
            right: parent.right
            margins: Style.collapsableSection.padding
        }
        height: collapsableSection.collapsed ? 0 : contentHeight + Style.collapsableSection.spacing * 2
        clip: true
        interactive: false
        spacing: Style.collapsableSection.spacing

        Behavior on height {
            NumberAnimation { duration: 150 }
        }
    }

    MouseArea {
        anchors.fill: sectionTitle
        onClicked: {
            if (collapsableSection.collapsed) {
                collapsableSection.expand()
            } else {
                collapsableSection.collapse()
            }
        }
    }
}
