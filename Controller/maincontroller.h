#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QGeoCoordinate>
#include <Controller/mapcontroller.h>
#include <Controller/mapmouseactioncontroller.h>
#include <Controller/actioncontroller.h>

class QQmlApplicationEngine;


namespace atlas::controller{
class  MapDrawer;

    class MainController : public QObject
    {
    public:
        MainController(QObject *parent = nullptr);

        void init(QQmlApplicationEngine* engine);
    private:
        MapController mMapController;
        MapDrawer*   mMapDrawer;
        MapMouseActionController mMapMouseActionController;
        ActionController mActionController;

        bool leftClicked;
        bool rightclicked;
        bool end = 1;
        bool start = 0;



    public slots:
        void initialLine();
        void endDraw(const QGeoCoordinate& coor);
        void setBeginLine(const QGeoCoordinate& coor);
        void setEndLine(const QGeoCoordinate& coor);

    };
}
#endif // MAINCONTROLLER_H
