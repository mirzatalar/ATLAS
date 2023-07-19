#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGeoCoordinate>
#include <GUI/models/EntityType.h>

class Entity
{
public:
    Entity();
    Entity(int mId, EntityType mType, QGeoCoordinate mCoordinate, int mHeading, int mSpeed);
    int mId;
    EntityType mType;
    QString mIcon;
    QString ReelIcon;
    QString highlitedIcon;
    QGeoCoordinate mCoordinate;
    int mHeading;
    int mSpeed;
    bool mIsHighlited;
    QString typeName;


};

#endif // ENTITY_H
