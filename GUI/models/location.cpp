#include "location.h"

Location::Location()
{

}

Location::Location(int mId, QGeoCoordinate mCoordinate)
{
    this->mId = mId;
    this->mCoordinate = mCoordinate;
}
