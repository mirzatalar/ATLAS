#ifndef PATH_H
#define PATH_H

#include <QGeoCoordinate>
#include <QVariantList>

class Path
{
public:
    Path();
    Path(int mId, QList<QGeoCoordinate> mPoints, QString mColor);
    int mId;
    QString mColor;
    QList<QGeoCoordinate> mPoints;
    bool mIsVisible;
    double mOpacity;
    bool mIsHighlited;


};

#endif // PATH_H
