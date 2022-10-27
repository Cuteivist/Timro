import QtQuick
import QtQuick.Controls

ImageButton {
    id: button

    property bool animationRunning: button.hovered && enabled

    width: 64
    height: 64
    layer.enabled: true
    layer.effect: ShaderEffect {
        id: shader
        property int rotationAngle: 0.0
        property real rotation: qmlHelper.degreeToRadians(rotationAngle)

        PropertyAnimation {
            id: rotationAnimation
            target: shader
            property: "rotation"
            from: 0
            to: 360
            duration: 100000
            loops: Animation.Infinite
            running: true
            paused: !animationRunning
        }

        fragmentShader: "qrc:/resources/shaders/buttonRotate.frag.qsb"
    }
}
