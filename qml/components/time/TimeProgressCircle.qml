import QtQuick
import QtQuick.Shapes

Item {
    id: root
    property int currentValue: 0
    property int maxValue: 0

    readonly property alias radius: timeInnerArc.radiusX

    Shape {
        anchors.fill: parent
        ShapePath {
            id: backgroundShapePath
            fillColor: "transparent"
            strokeColor: "#80808080"
            strokeWidth: 2
            capStyle: ShapePath.FlatCap

            PathAngleArc {
                id: timeInnerArc
                centerX: shape.center.x
                centerY: shape.center.y
                radiusX: timeBar.height * 0.45
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

    Shape {
        id: shape

        readonly property point center: Qt.point(timeBar.width * 0.5, timeBar.height * 0.5)
        readonly property int barLineHeight: timeBar.height * 0.05

        property int currentAngle: (currentValue / maxValue) * 360

        function rotatePoint(c, angle, p) {
            const degree = angle * (Math.PI/180);
            var sin = Math.sin(degree);
            var cos = Math.cos(degree);

            // translate point back to origin:
            p.x -= c.x;
            p.y -= c.y;

            // rotate point
            var xnew = p.x * cos - p.y * sin;
            var ynew = p.x * sin + p.y * cos;

            // translate point back:
            p.x = xnew + c.x;
            p.y = ynew + c.y;
            return p;
        }

        function getFinishLineInnerPoint() {
            return rotatePoint(shape.center, shape.currentAngle, Qt.point(shape.center.x, shape.center.y + timeInnerArc.radiusX - shape.barLineHeight * 0.5))
        }

        function getFinishLineOuterPoint() {
            return rotatePoint(shape.center, shape.currentAngle, Qt.point(shape.center.x, shape.center.y + timeInnerArc.radiusX + shape.barLineHeight * 0.5))
        }

        anchors.fill: parent
        layer.enabled: true
        layer.smooth: true
        layer.samples: 4
        layer.samplerName: "maskSource"
        layer.effect: ShaderEffect {
            property var colorSource: gradientRect
            fragmentShader: "qrc:/resources/shaders/linearGradient.frag.qsb"
        }

        ShapePath {
            fillColor: "transparent"
            strokeColor: "red"
            strokeWidth: 4
            capStyle: ShapePath.RoundCap

            startX: shape.center.x
            startY: shape.center.y + timeInnerArc.radiusX - shape.barLineHeight * 0.5
            PathLine {
                x: shape.center.x
                relativeY: shape.barLineHeight
            }
            PathMove {
                x: shape.getFinishLineInnerPoint().x
                y: shape.getFinishLineInnerPoint().y
            }

            PathLine {
                x: shape.getFinishLineOuterPoint().x
                y: shape.getFinishLineOuterPoint().y
            }
            PathAngleArc {
                centerX: shape.center.x
                centerY: shape.center.y
                radiusX: timeInnerArc.radiusX
                radiusY: radiusX
                startAngle: 90
                sweepAngle: shape.currentAngle
            }
        }
    }

}
