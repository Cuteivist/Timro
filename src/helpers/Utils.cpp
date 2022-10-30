#include "Utils.h"

#include <QCursor>
#include <QDebug>

using namespace Qt::Literals::StringLiterals;

Utils::Utils(QObject *parent)
    : QObject{parent}
{
}

QPoint Utils::cursorPos()
{
    return QCursor::pos();
}

QPointF Utils::rotatePoint(const QPointF &center, const double angle, const QPointF &point)
{
    const float radians = qDegreesToRadians(angle);
    const float sin = qSin(radians);
    const float cos = qCos(radians);

    QPointF result = point;
    // translate point back to origin:
    result -= center;
    // rotate point
    const float xNew = result.x() * cos - result.y() * sin;
    const float yNew = result.x() * sin + result.y() * cos;
    // translate point back:
    result = center + QPointF(xNew, yNew);

    return result;
}

float Utils::degreeToRadians(const float degree)
{
    return qDegreesToRadians(degree);
}

int Utils::getMinutes(const int seconds)
{
    return qFloor(static_cast<float>(seconds) / 60.f) % 60;
}

int Utils::getHours(const int seconds)
{
    return qFloor(qFloor(static_cast<float>(seconds) / 60.f) / 60);
}

QString Utils::secondsToTimeString(const int seconds, const bool showSeconds)
{
    const int fullMinutes = qFloor(seconds / 60);
    const int mins = fullMinutes % 60;
    const int hours = qFloor(fullMinutes / 60);

    const QString minutesStr = timeToStringWithLeadingZero(mins);
    const QString hoursStr = timeToStringWithLeadingZero(hours);

    if (showSeconds) {
        const int secs = seconds % 60;
        const QString secondsStr = timeToStringWithLeadingZero(secs);
        return u"%1:%2:%3"_s.arg(hoursStr, minutesStr, secondsStr);
    }
    return u"%1:%2"_s.arg(hoursStr, minutesStr);
}

QString Utils::timeToStringWithLeadingZero(const int elapsed)
{
    return elapsed > 9 ? QString::number(elapsed) : u"0%1"_s.arg(elapsed);
}
