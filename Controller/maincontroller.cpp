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




    //TESTS
    mMapDrawer = new MapDrawer(nullptr,engine);
    QGeoCoordinate b;
    b.setLatitude(39);
    b.setLongitude(39);

    QGeoCoordinate c;
    c.setLatitude(41);
    c.setLongitude(31);
    QGeoCoordinate d;
    d.setLatitude(43);
    d.setLongitude(36);
    QGeoCoordinate e;
    e.setLatitude(45);
    e.setLongitude(36);

    QGeoCoordinate f;
    f.setLatitude(37);
    f.setLongitude(39);


    mMapDrawer->drawLine(18,b,a,"red");
    mMapDrawer->drawCircle(25,b,"pink");
    mMapDrawer->setColor(18,"blue");
    mMapDrawer->setColor(25,"white");

    mMapDrawer->setHighlight(18,1);
    mMapDrawer->setHighlight(25,1);

    mMapDrawer->setOpacity(18,0.5);
    mMapDrawer->setOpacity(25,0.5);
    //mMapDrawer->setVisibility(18,0);
    //mMapDrawer->setVisibility(25,0);


   //mMapDrawer->move(18,c);
   // mMapDrawer->move(25,c);

    mMapDrawer->setHighlight(18,0);
    mMapDrawer->setHighlight(25,0);

    mMapDrawer->addPosition(a);
    mMapDrawer->addPosition(b);
    mMapDrawer->addPosition(c);
    mMapDrawer->addPosition(d);
    mMapDrawer->addPosition(e);
    mMapDrawer->addPosition(f);





}
