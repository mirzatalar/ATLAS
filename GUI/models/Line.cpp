#include "line.h"

Line::Line()
{

}

Line::Line(int mId, QGeoCoordinate mCoordinate1, QGeoCoordinate mCoordinate2, QString mColor,  bool mIsVisible, bool mIsHighlited)
{
    this->mId = mId;
    this->mCoordinate1 = mCoordinate1;
    this->mCoordinate2 = mCoordinate2;
    this->mColor = mColor;
    this->mIsVisible = mIsVisible;
    this->mIsHighlited = mIsHighlited;
}
