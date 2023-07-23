#include "location.h"

Location::Location()
{

}

Location::Location(int mId, QGeoCoordinate mCoordinate, QString name)
{
    this->mId = mId;
    this->mCoordinate = mCoordinate;
    this->name = name;
}
