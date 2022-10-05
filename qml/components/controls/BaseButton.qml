import QtQuick
import QtQuick.Controls

import "../"

Button {
    id: button
    flat: true
    background: Item { }

    contentItem: AutoSizeText {
        text: button.text
    }
}
