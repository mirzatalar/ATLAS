#ifndef PATH_H
#define PATH_H

#include <QGeoCoordinate>
#include <QVariantList>

class Path
{
public:
    Path();
    Path(int mId, QVariantList mPoints, QString mColor);
    int mId;
    QString mColor;
    QVariantList mPoints;

};

#endif // PATH_H
