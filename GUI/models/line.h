#ifndef LINE_H
#define LINE_H


#include <QObject>
#include <QGeoCoordinate>

class Line {
public:
    Line();
    Line(int mId, QGeoCoordinate mCoordinate1, QGeoCoordinate mCoordinate2, QString mColor);
    int mId;
    QString mColor;
    bool mIsVisible;
    double mOpacity;
    bool mIsHighlited;
    QGeoCoordinate mCoordinate1;
    QGeoCoordinate mCoordinate2;
    int distance;



};

#endif // LINE_H
