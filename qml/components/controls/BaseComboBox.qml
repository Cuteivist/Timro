import QtQuick
import QtQuick.Controls

import ".."

ComboBox {
    id: comboBox

    property real textOpacity: 1.0

    contentItem: Item {
        width: comboBox.width
        height: comboBox.height
        AutoSizeText {
            anchors.fill: parent
            verticalAlignment: Qt.AlignVCenter
            text: comboBox.currentText
            opacity: textOpacity
        }
    }
    background: Item {}
    popup: Popup {
        y: -comboBox.height / 2
        width: comboBox.width
        implicitHeight: contentItem.implicitHeight
        padding: 0

        contentItem: ListView {
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            width: comboBox.width
            implicitHeight: contentHeight
            model: comboBox.delegateModel
            currentIndex: highlightedIndex
            highlightFollowsCurrentItem: true

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }
    delegate: ItemDelegate {
        hoverEnabled: true
        width: ListView.view.width
        text: comboBox.textAt(index)
        highlighted: comboBox.highlightedIndex === index
        palette.highlight: "#600000FF"
    }
}
