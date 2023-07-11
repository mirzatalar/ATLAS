#ifndef CIRCLE_H
#define CIRCLE_H
#include <QObject>
#include <QGeoCoordinate>

class Circle
{
public:
    Circle();

    Circle(int mId, QGeoCoordinate mCenter, QString mColor);
    int mId;
    QString mColor;
    bool mIsVisible;
    double mOpacity;
    bool mIsHighlited;
    QGeoCoordinate mCenter;
};

#endif // CIRCLE_H
