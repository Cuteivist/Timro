import QtQuick
import QtQuick.Controls

import Timro

ComboBox {
    id: comboBox

    property real textOpacity: 1.0
    property bool autoAdjustPopupWidth: false

    QtObject {
        id: priv
        property real popupWidth: comboBox.width
    }

    function refreshPopupWidth() {
        if (!autoAdjustPopupWidth) {
            return
        }

        comboBoxFontMetrics.font = comboBox.font
        let longestWordLength = 0
        let longestWords = []
        for (var i = 0 ; i < count ; i++) {
            const name = comboBox.textAt(i)
            if (name.length > longestWordLength) {
                longestWordLength = name.length
                longestWords = [ name ]
            } else if (name.length === longestWordLength) {
                longestWords.push(name)
            }
        }

        // It is possible to get more than one string with same letter count,
        // but with different painted width
        let longestWordWidth = 0
        for (var i = 0 ; i < longestWords.length ; i++) {
            const textRect = comboBoxFontMetrics.boundingRect(longestWords[i])
            if (textRect.width > longestWordWidth) {
                longestWordWidth = textRect.width
            }
        }
        priv.popupWidth = Math.min(mainWindow.width, longestWordWidth)
    }

    FontMetrics {
        id: comboBoxFontMetrics
    }

    onCountChanged: refreshPopupWidth()
    onModelChanged: refreshPopupWidth()
    onFontChanged: refreshPopupWidth()

    font.pixelSize: Style.comboBox.defaultFontSize
    contentItem: Text {
        text: comboBox.currentText
        rightPadding: comboBox.indicator.width + comboBox.spacing
        elide: Text.ElideRight
        opacity: textOpacity
        font: comboBox.font
    }
    indicator: Image {
        x: comboBox.width - width - comboBox.rightPadding
        y: (comboBox.height - height) * 0.5
        width: Style.comboBox.indicatorSize
        height: width
        source: "qrc:/Timro/resources/button/down.png"
        rotation: comboBox.down ? 180 : 0
    }
    background: Item {}
    popup: Popup {
        width: Math.max(comboBox.width, priv.popupWidth)
        implicitHeight: contentItem.implicitHeight
        padding: 0

        contentItem: ListView {
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            implicitHeight: contentHeight
            model: comboBox.delegateModel
            currentIndex: highlightedIndex
            highlightFollowsCurrentItem: true

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }
    delegate: ItemDelegate {
        indicator: Rectangle {
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 5
            }
            width: Style.comboBox.selectedIndicatorSize
            height: width
            radius: width * 0.5
            color: Style.comboBox.selectedIndicatorColor
            visible: currentIndex === index
        }

        leftPadding: indicator.width * 2
        hoverEnabled: true
        width: ListView.view.width
        text: comboBox.textAt(index)
        highlighted: comboBox.highlightedIndex === index
        palette.highlight: Style.comboBox.highlightColor
    }
}
