import QtQuick
import QtQuick.Controls

Button {
    id: button

    property string source

    width: 24
    height: 24
    display: AbstractButton.IconOnly
    flat: true
    background: Item { }

    contentItem: Image {
        source: button.source
        width: button.width
        height: button.width
    }
}
