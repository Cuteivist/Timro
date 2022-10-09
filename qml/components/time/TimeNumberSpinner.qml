import QtQuick
import QtQuick.Controls

Tumbler {
    id: root

    property int currentValue: startValue
    property int startValue: 0
    property int endValue: 99

    Component.onCompleted: {
        let modelArray = []
        for (var i = startValue ; i <= endValue ; i++) {
            let value = i > 9 ? '' + i : '0' + i
            modelArray.push(value)
        }
        model = modelArray
    }
    model: []
    visibleItemCount: 3
    wrap: true

    layer.enabled: true
    layer.effect: ShaderEffect {
        fragmentShader: "qrc:/resources/shaders/timeListOpacity.frag.qsb"
    }
    delegate: Text {
        width: root.width
        height: root.height / visibleItemCount
        horizontalAlignment: Qt.AlignHCenter
        text: modelData
        font.pixelSize: 50
        minimumPixelSize: 10
        fontSizeMode: Text.Fit
        scale: Math.abs(Tumbler.displacement) > 0.5 ? 0.7 : 1.0

        Behavior on scale {
            NumberAnimation {
                duration: 150
            }
        }
    }
}
