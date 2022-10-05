import QtQuick
import QtQuick.Controls

BaseButton {
    id: button

    property string source
    property real iconSize: width

    width: 24
    height: 24
    display: AbstractButton.IconOnly
    background: Item { }

    contentItem: Image {
        source: button.source
        width: button.iconSize
        height: button.iconSize
        smooth: true
    }
}
