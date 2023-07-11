#ifndef LINE_H
#define LINE_H


#include <QObject>
#include <QGeoCoordinate>

class Line {
public:
    Line();
    Line(int mId, QGeoCoordinate mCoordinate1, QGeoCoordinate mCoordinate2, QString mColor,  bool mIsVisible, bool mIsHighlited);
    int mId;
    QString mColor;
    bool mIsVisible;
    bool mIsHighlited;
    QGeoCoordinate mCoordinate1;
    QGeoCoordinate mCoordinate2;



};

#endif // LINE_H
