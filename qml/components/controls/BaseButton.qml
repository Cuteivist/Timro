import QtQuick
import QtQuick.Controls

import "../"

Button {
    id: button

    property int textHorizontalAlignment: Text.AlignLeft
    property int textVerticalAlignment: Text.AlignTop

    flat: true
    background: Item { }

    contentItem: Text {
        verticalAlignment: textVerticalAlignment
        horizontalAlignment: textHorizontalAlignment
        text: button.text
        font: button.font
    }
}
