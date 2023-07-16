#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QGeoCoordinate>,
#include <QGeoRectangle>
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
        bool rightclicked = 0;
        bool end = 1;
        bool start = 0;
        int option;
        QString clor = "black";
        int itemCount = 0;
        bool gridOn = false;

        QGeoCoordinate topLeft;
        QGeoCoordinate bottomRight;
        QGeoCoordinate cntr;




    public slots:
        void initialLine();
        void RightClicked(const QGeoCoordinate& coor);
        void LeftClicked(const QGeoCoordinate& coor);
        void DoubleClicked(const QGeoCoordinate& coor);
        void Position(const QGeoCoordinate& coor);
        void StartAction(int opt);
        void ChangeColor(const QString &clr);
        void highlight(int id);
        void setZoom(int zoomLevel);
        void setBearing(int zoomLevel);
        void setTilt(int zoomLevel);
        void grid(const QGeoRectangle &rec);
        void center(const QGeoCoordinate& coor);
        void gocenter();



    };
}
#endif // MAINCONTROLLER_H
