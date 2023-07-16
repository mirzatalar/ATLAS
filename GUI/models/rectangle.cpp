#include "rectangle.h"

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(QGeoCoordinate coor1, QGeoCoordinate coor2)
{
    this->coor1 = coor1;
    this->coor2 = coor2;

}
