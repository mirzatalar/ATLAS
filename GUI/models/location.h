#ifndef LOCATION_H
#define LOCATION_H

#include <QGeoCoordinate>


class Location
{
public:
    Location();
    Location(int mId, QGeoCoordinate mCoordinate);
    int mId;
    bool mIsHighlited;
    QGeoCoordinate mCoordinate;
    QString icon;
    QString highLitedcon;
};

#endif // LOCATION_H
