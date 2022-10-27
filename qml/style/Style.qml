pragma Singleton

import QtQuick

QtObject {
    id: style

    readonly property var global: QtObject {
        readonly property int defaultFontSize: 18
        readonly property int smallFontSize: 15
    }

    readonly property var timeDisplay: QtObject {
        readonly property color backgroundCircleColor: "#80808080"
        readonly property color editCircleColor: "#FA0942"
        readonly property color editCircleAnimationColor: "#FF9DA3"
        readonly property int textFontSize: 27
        readonly property int editTextFontSize: 35
    }

    readonly property var editIcon: QtObject {
        readonly property int size: 24
    }

    readonly property var editField: QtObject {
        readonly property color inputFieldColor: "#A0FFFFFF"
    }

    readonly property var listDelegate: QtObject {
        readonly property int height: 40
        readonly property int radius: 4
        readonly property color backgroundColor: "#80FFFFFF"
        readonly property int borderWidth: 1
        readonly property color borderColor: "black"
        readonly property int fontSize: 18
        readonly property int listSpacing: 5
        readonly property int spacing: 5
    }

    readonly property var panel: QtObject {
        readonly property int padding: 5
        readonly property int titleFontSize: global.defaultFontSize
        readonly property color backgroundColor: "#4C8EA8C1"
        readonly property int radius: 20
        readonly property int panelListSpacing: 10
        readonly property int titleHeight: 30
    }

    readonly property var background: QtObject {
        readonly property color appColor: "#DDD4E6"
    }

    readonly property var dialog: QtObject {
        readonly property int titleFontSize: global.defaultFontSize
        readonly property int contentItemFontSize: 30
        readonly property int buttonFontSize: global.defaultFontSize
        readonly property int buttonRowSpacing: 10
        readonly property color backgroundColor: "#DDD4E6"
    }

    readonly property var mainMenu: QtObject {
        readonly property int iconSize: 32
        readonly property color backgroundColor: "#1981A1"
        readonly property color separatorColor: "white"
        readonly property color activeColor: "#4CFFFFFF"
    }

    readonly property var comboBox: QtObject {
        readonly property color selectedIndicatorColor: "#1981A1"
        readonly property int selectedIndicatorSize: 10
        readonly property color highlightColor: "#600000FF"
        readonly property int indicatorSize: 12
        readonly property int defaultFontSize: global.smallFontSize
    }
}
