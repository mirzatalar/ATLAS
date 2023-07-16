#ifndef MAPDRAWER_H
#define MAPDRAWER_H

#include "qqmlapplicationengine.h"

#include <QObject>
#include <QGeoCoordinate>
#include <QGeoRectangle>
#include <GUI/models/linemodel.h>
#include <GUI/models/circlemodel.h>
#include <QQmlEngine>
#include "GUI/models/pathmodel.h"
#include "GUI/models/rectanglemodel.h"
#include "GUI/models/gridmodel.h"
#include <QVariantList>
namespace  atlas :: controller
{

    class MapDrawer : public QObject
    {
        Q_OBJECT
    public:
        explicit MapDrawer(QObject *parent, QQmlApplicationEngine *engine);


        bool drawLine(int mId,const QGeoCoordinate &coordinate1,const QGeoCoordinate &coordinate2,const QString &mColor);
        bool setEndLine(int mId,const QGeoCoordinate &coordinate2);
        bool setEndLineC(int mId,const QGeoCoordinate &coordinate2);
        bool setBeginLine(int mId,const QGeoCoordinate &coordinate1);
        bool drawCircle(int mId,const QGeoCoordinate &mCenter,const QGeoCoordinate &mCircumCoor,const QString &mColor);
        bool drawRectangle(const QGeoCoordinate &m1,const QGeoCoordinate &m2);

        bool drawPath(int mId,const QList<QGeoCoordinate>& points,const QString& mColor);
        bool updatePath(int mId, bool request,const QGeoCoordinate &coordinate);


        bool removeRec();
        bool setEndLineR(const QGeoCoordinate &coordinate2);

        bool remove(int mId);
        bool move(int mId,const QGeoCoordinate &mPos);
        bool moveAll(int count,const QGeoCoordinate &mPos,const QGeoCoordinate &midPoint);
        bool setHighlight(int mId, bool status);
        bool setVisibility(int mId, bool status);
        bool setOpacity(int mId, double mOpacity);
        bool setColor(int mId,const QString &mColor);
        bool isExist(int mId);
        bool createGrid( const QGeoRectangle &rec);
        void clearGrid( );
        void deleteAll(int count);

        bool setHighlightAll(int count,const QGeoCoordinate &m1, const QGeoCoordinate &m2);
        QGeoCoordinate midPoint();


    private:
        atlas::gui::LineModel mLineModel;
        atlas::gui::CircleModel mCircleModel;
        atlas::gui::PathModel mPathModel;
        atlas::gui::RectangleModel mRectangleModel;
        atlas::gui::GridModel mGridModel;;

    };
}
#endif // MAPDRAWER_H
