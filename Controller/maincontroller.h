#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QGeoCoordinate>
#include <Controller/mapcontroller.h>
#include <Controller/mapmouseactioncontroller.h>

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
        QGeoCoordinate coor;


    public slots:
        void mouseSignalHandler(const QGeoCoordinate& coor);

    };
}
#endif // MAINCONTROLLER_H
