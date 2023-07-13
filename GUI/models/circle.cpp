#include "circle.h"

Circle::Circle()
{

}

Circle::Circle(int mId, QGeoCoordinate mCenter,QGeoCoordinate mCircumCoor, QString mColor)
{
    this->mId = mId;
    this->mCenter = mCenter;
    this->mCircumCoor = mCircumCoor;
    this->mColor = mColor;
}
