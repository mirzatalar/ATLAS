#ifndef MAPDRAWER_H
#define MAPDRAWER_H

#include "qqmlapplicationengine.h"

#include <QObject>
#include <QGeoCoordinate>
#include <GUI/models/linemodel.h>
#include <GUI/models/circlemodel.h>
#include <QQmlEngine>
#include "GUI/models/pathmodel.h"
#include <QVariantList>
namespace  atlas :: controller
{

    class MapDrawer : public QObject
    {
        Q_OBJECT
    public:
        explicit MapDrawer(QObject *parent, QQmlApplicationEngine *engine);


        bool drawLine(int mId,const QGeoCoordinate &coordinate1,const QGeoCoordinate &coordinate2,const QString &mColor);
        bool drawCircle(int mId,const QGeoCoordinate &mCenter,const QString &mColor);
        bool drawPath(int mId,const QList<QGeoCoordinate>& points,const QString& mColor);
        bool updatePath(int mId, bool request,const QGeoCoordinate &coordinate);




        bool remove(int mId);
        bool move(int mId,const QGeoCoordinate &mPos);
        bool setHighlight(int mId, bool status);
        bool setVisibility(int mId, bool status);
        bool setOpacity(int mId, double mOpacity);
        bool setColor(int mId,const QString &mColor);



    private:
        atlas::gui::LineModel mLineModel;
        atlas::gui::CircleModel mCircleModel;
        atlas::gui::PathModel mPathModel;

    };
}
#endif // MAPDRAWER_H
