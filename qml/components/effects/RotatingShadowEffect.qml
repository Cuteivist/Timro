import QtQuick 2.15

ShaderEffect {
    id: effect
    property int shadowCount: 4
    property color shadowColor: "white"
    property real currentAngle: 0.0
    property int duration: 8000

    readonly property point ratio: Qt.point(Math.min(1.0, width / height), Math.min(1.0, height / width))

    UniformAnimator on currentAngle {
       loops: Animation.Infinite
       from: 0
       to: 360
       duration: effect.duration
       running: visible
    }
    fragmentShader: "qrc:/resources/shaders/rotatingShadow.frag.qsb"
}
