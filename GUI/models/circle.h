#ifndef CIRCLE_H
#define CIRCLE_H
#include <QObject>
#include <QGeoCoordinate>

class Circle
{
public:
    Circle();

    Circle(int mId, QGeoCoordinate mCenter,QGeoCoordinate mCircumCoor, QString mColor);
    int mId;
    QString mColor;
    bool mIsVisible;
    double mOpacity;
    bool mIsHighlited;
    int radius;
    QGeoCoordinate mCenter;
    QGeoCoordinate mCircumCoor;
    long area;

};

#endif // CIRCLE_H
