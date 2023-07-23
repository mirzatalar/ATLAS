#ifndef LOCATION_H
#define LOCATION_H

#include <QGeoCoordinate>


class Location
{
public:
    Location();
    Location(int mId, QGeoCoordinate mCoordinate, QString name);
    int mId;
    bool mIsHighlited;
    QGeoCoordinate mCoordinate;
    QString icon;
    QString highLitedcon;
    QString name;
};

#endif // LOCATION_H
