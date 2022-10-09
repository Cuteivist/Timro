import QtQuick
import QtQuick.Controls

import "../"

Button {
    id: button

    property int textHorizontalAlignment: Text.AlignLeft

    flat: true
    background: Item { }

    contentItem: AutoSizeText {
        horizontalAlignment: textHorizontalAlignment
        text: button.text
    }
}
