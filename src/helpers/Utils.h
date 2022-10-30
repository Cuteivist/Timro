#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);
    Q_DISABLE_COPY(Utils)

    Q_INVOKABLE static QPoint cursorPos();

    // Drawing
    Q_INVOKABLE static QPointF rotatePoint(const QPointF &center, const double angle, const QPointF &point);
    Q_INVOKABLE static float degreeToRadians(const float degree);

    // Time
    Q_INVOKABLE static int getMinutes(const int seconds);
    Q_INVOKABLE static int getHours(const int seconds);
    Q_INVOKABLE static QString secondsToTimeString(const int seconds, const bool showSeconds = true);
    Q_INVOKABLE static QString timeToStringWithLeadingZero(const int elapsed);

};

#endif // UTILS_H
