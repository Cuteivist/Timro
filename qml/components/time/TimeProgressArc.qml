import QtQuick
import QtQuick.Shapes

Shape {
    id: arcShape

    property int radius: 0
    property real progress: 0

    QtObject {
        id: priv
        readonly property point center: Qt.point(arcShape.width * 0.5, arcShape.height * 0.5)
        readonly property int barLineHeight: arcShape.height * 0.05
        readonly property int currentAngle: Math.min(360, arcShape.progress * 360)

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
            return rotatePoint(priv.center, priv.currentAngle, Qt.point(priv.center.x, priv.center.y + arcShape.radius - priv.barLineHeight * 0.5))
        }

        function getFinishLineOuterPoint() {
            return rotatePoint(priv.center, priv.currentAngle, Qt.point(priv.center.x, priv.center.y + arcShape.radius + priv.barLineHeight * 0.5))
        }
    }

    layer.enabled: true
    layer.smooth: true
    layer.samples: 4

    ShapePath {
        fillColor: "transparent"
        strokeColor: "red"
        strokeWidth: 4
        capStyle: ShapePath.RoundCap

        startX: priv.center.x
        startY: priv.center.y + arcShape.radius - priv.barLineHeight * 0.5
        PathLine {
            x: priv.center.x
            relativeY: priv.barLineHeight
        }
        PathMove {
            x: priv.getFinishLineInnerPoint().x
            y: priv.getFinishLineInnerPoint().y
        }

        PathLine {
            x: priv.getFinishLineOuterPoint().x
            y: priv.getFinishLineOuterPoint().y
        }
        PathAngleArc {
            centerX: priv.center.x
            centerY: priv.center.y
            radiusX: arcShape.radius
            radiusY: radiusX
            startAngle: 90
            sweepAngle: priv.currentAngle
        }
    }
}
