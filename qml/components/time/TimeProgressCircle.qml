import QtQuick
import QtQuick.Shapes

import "../effects"

Item {
    id: progressCircle
    property int currentValue: 0
    property int maxValue: 0
    property bool editMode: false
    property int editValue: 0

    readonly property alias radius: timeInnerArc.radiusX

    Shape {
        anchors.fill: parent
        ShapePath {
            fillColor: "transparent"
            strokeColor: "#80808080"
            strokeWidth: 2
            capStyle: ShapePath.FlatCap

            PathAngleArc {
                id: timeInnerArc
                centerX: progressCircle.width * 0.5
                centerY: progressCircle.height * 0.5
                radiusX: progressCircle.height * 0.45
                radiusY: radiusX
                startAngle: 90
                sweepAngle: 360
            }
        }
    }

    Rectangle {
        id: gradientRect
        anchors.fill: parent
        gradient: LinearGradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.3; color: "blue" }
            GradientStop { position: 0.8; color: "red" }
        }
        visible: false
        layer.enabled: true
        layer.smooth: true
    }

    TimeProgressArc {
        id: currentTimeArc
        radius: timeInnerArc.radiusX
        progress: currentValue / maxValue
        anchors.fill: parent
        layer.effect: GradientEffect {
            sourceRect: gradientRect
        }
    }

    TimeProgressArc {
        id: editTimeArc
        anchors.fill: parent
        radius: timeInnerArc.radiusX * 1.07
        visible: editMode
        progress: editValue / maxValue
        color: "#FA0942"
        layer.effect: RotatingShadowEffect {
            shadowCount: 10
            shadowColor: "#FF9DA3"
        }
    }
}
