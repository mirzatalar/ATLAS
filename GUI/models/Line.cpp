#include "line.h"

Line::Line()
{

}

Line::Line(int mId, QGeoCoordinate mCoordinate1, QGeoCoordinate mCoordinate2, QString mColor)
{
    this->mId = mId;
    this->mCoordinate1 = mCoordinate1;
    this->mCoordinate2 = mCoordinate2;
    this->mColor = mColor;
}
