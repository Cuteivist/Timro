import QtQuick
import QtQuick.Controls

ImageButton {
    id: button

    width: 64
    height: 64
    layer.enabled: true
    layer.effect: ShaderEffect {
        id: shader
        readonly property real translationValue: (Math.PI / 180)
        property int rotationAngle: 0.0
        property real rotation: rotationAngle * translationValue

        PropertyAnimation {
            id: rotationAnimation
            target: shader
            property: "rotation"
            from: 0
            to: 360
            duration: 100000
            loops: Animation.Infinite
            running: true
            paused: !button.hovered
        }

        fragmentShader: "qrc:/resources/shaders/buttonRotate.frag.qsb"
    }
}
