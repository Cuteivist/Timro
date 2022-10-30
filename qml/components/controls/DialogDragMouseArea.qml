import QtQuick

MouseArea {
    property point startDialogPos
    property point startCursorPos
    property var window: null

    anchors.fill: parent
    onPressed: {
        if (window === null) {
            return
        }

        // remember starting position
        startDialogPos = Qt.point(window.x, window.y);
        startCursorPos = utils.cursorPos();
    }

    onPositionChanged: {
        if (window === null) {
            return
        }
        // count difference
        const newCursorPos = utils.cursorPos();
        const difference = Qt.point(newCursorPos.x - startCursorPos.x,
                                    newCursorPos.y - startCursorPos.y);
        // update position
        window.x = startDialogPos.x + difference.x;
        window.y = startDialogPos.y + difference.y;
    }
}
