#include "QmlHelper.h"

#include <QCursor>
#include <QDebug>

using namespace Qt::Literals::StringLiterals;

QmlHelper::QmlHelper(QObject *parent)
    : QObject{parent}
{

}

QPoint QmlHelper::cursorPos() const
{
    return QCursor::pos();
}

QPointF QmlHelper::rotatePoint(const QPointF &center, const double angle, const QPointF &point) const
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

float QmlHelper::degreeToRadians(const float degree) const
{
    return qDegreesToRadians(degree);
}

int QmlHelper::getMinutes(const int seconds) const
{
    return qFloor(static_cast<float>(seconds) / 60.f) % 60;
}

int QmlHelper::getHours(const int seconds) const
{
    return qFloor(qFloor(static_cast<float>(seconds) / 60.f) / 60);
}

QString QmlHelper::secondsToTimeString(const int seconds) const
{
    const int fullMinutes = qFloor(seconds / 60);
    const int secs = seconds % 60;
    const int mins = fullMinutes % 60;
    const int hours = qFloor(fullMinutes / 60);

    const QString secondsStr = timeToStringWithLeadingZero(secs);
    const QString minutesStr = timeToStringWithLeadingZero(mins);
    const QString hoursStr = timeToStringWithLeadingZero(hours);

    return u"%1:%2:%3"_s.arg(hoursStr, minutesStr, secondsStr);
}

QString QmlHelper::timeToStringWithLeadingZero(const int elapsed) const
{
    return elapsed > 9 ? QString::number(elapsed) : u"0%1"_s.arg(elapsed);
}
