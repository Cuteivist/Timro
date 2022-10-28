#ifndef QMLHELPER_H
#define QMLHELPER_H

#include <QObject>

class QmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit QmlHelper(QObject *parent = nullptr);
    Q_DISABLE_COPY(QmlHelper)

    Q_INVOKABLE QPoint cursorPos() const;

    // Drawing
    Q_INVOKABLE QPointF rotatePoint(const QPointF &center, const double angle, const QPointF &point) const;
    Q_INVOKABLE float degreeToRadians(const float degree) const;

    // Time
    Q_INVOKABLE int getMinutes(const int seconds) const;
    Q_INVOKABLE int getHours(const int seconds) const;
    Q_INVOKABLE QString secondsToTimeString(const int seconds) const;
    Q_INVOKABLE QString timeToStringWithLeadingZero(const int elapsed) const;
};

#endif // QMLHELPER_H
