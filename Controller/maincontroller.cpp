#include "maincontroller.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtPositioning>
#include <iostream>
#include <Controller/mapdrawer.h>

atlas::controller::MainController::MainController(QObject *parent):
    QObject(parent)
{


}

void atlas::controller::MainController::init(QQmlApplicationEngine *engine)
{
    //mapcontrol
    QQmlContext* ctx = engine->rootContext();
    ctx->setContextProperty("mapController",&mMapController);


    // mapcontrol tests
    QGeoCoordinate a;
    a.setLatitude(40);
    a.setLongitude(40);
    mMapController.setZoomLevel(8);
    mMapController.setCenter(a);
    mMapController.setTilt(0);
    mMapController.setBearing(0);





    mMapDrawer = new MapDrawer(nullptr,engine);

    //mapdrawer
asdasd

   //  map_drawer(nullptr,engine);




    QGeoCoordinate b;
    b.setLatitude(40);
    b.setLongitude(40);

    QGeoCoordinate c;
    c.setLatitude(41);
    c.setLongitude(31);

    mMapDrawer->drawLine(18,b,c,"red",1,1);
   // mMapDrawer->drawLine(21,b,c,"blue",1,1);



}
