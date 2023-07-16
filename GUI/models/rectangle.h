#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <QGeoCoordinate>

class Rectangle
{
public:
    Rectangle();
    Rectangle(QGeoCoordinate coor1,QGeoCoordinate coor2);
    QGeoCoordinate coor1;
    QGeoCoordinate coor2;
};

#endif // RECTANGLE_H
