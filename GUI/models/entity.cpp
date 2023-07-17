#include "entity.h"

Entity::Entity()
{

}

Entity::Entity(int mId, EntityType mType, QGeoCoordinate mCoordinate, int mHeading, int mSpeed)
{
    this->mId = mId;
    this->mType = mType;
    this->mHeading = mHeading;
    this->mSpeed = mSpeed;
    this->mCoordinate = mCoordinate;
}
