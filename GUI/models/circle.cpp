#include "circle.h"

Circle::Circle()
{

}

Circle::Circle(int mId, QGeoCoordinate mCenter, QString mColor)
{
    this->mId = mId;
    this->mCenter = mCenter;
    this->mColor = mColor;
}
