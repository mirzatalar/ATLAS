#ifndef MAPDRAWER_H
#define MAPDRAWER_H

#include "qqmlapplicationengine.h"

#include <QObject>
#include <QGeoCoordinate>
#include <GUI/models/linemodel.h>
#include <QQmlEngine>
namespace  atlas :: controller
{

    class MapDrawer : public QObject
    {
        Q_OBJECT
    public:
        explicit MapDrawer(QObject *parent, QQmlApplicationEngine *engine);
        bool drawLine(int mId,const QGeoCoordinate &coordinate1,const QGeoCoordinate &coordinate2,const QString &mColor, bool IsHighlited, bool IsVisible);
        bool removeLine(int mId);


    private:
        atlas::gui::LineModel mLineModel;

    };
}
#endif // MAPDRAWER_H
