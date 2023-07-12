#include "maincontroller.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtPositioning>
#include <iostream>
#include <Controller/mapdrawer.h>
#include <csignal>

atlas::controller::MainController::MainController(QObject *parent):
    QObject(parent)
{


}

void atlas::controller::MainController::init(QQmlApplicationEngine *engine)
{
    //mapcontrol
    QQmlContext* ctx = engine->rootContext();
    ctx->setContextProperty("mapController",&mMapController);
    ctx->setContextProperty("mapMouseActionController",&mMapMouseActionController);


    // mapcontrol tests
    QGeoCoordinate a;
    a.setLatitude(40);
    a.setLongitude(40);
    mMapController.setZoomLevel(1);
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


//    mMapDrawer->drawLine(18,b,a,"red");
//    mMapDrawer->drawLine(19,b,e,"black");
//    mMapDrawer->drawCircle(25, mMapMouseActionController.tester,"pink");
    mMapDrawer->drawCircle(26,a,"blue");

//    mMapDrawer->setColor(18,"blue");
//    mMapDrawer->setColor(25,"white");

//    mMapDrawer->setHighlight(18,1);
//    mMapDrawer->setHighlight(25,1);
//    mMapDrawer->setHighlight(26,1);

//    mMapDrawer->setOpacity(18,0.5);
//    mMapDrawer->setOpacity(25,0.5);
//    mMapDrawer->setVisibility(19,1);
//    mMapDrawer->setVisibility(26,1);


   //mMapDrawer->move(18,c);
   // mMapDrawer->move(25,c);

//    mMapDrawer->setHighlight(18,0);
//    mMapDrawer->setHighlight(25,0);

//    mMapDrawer->addPosition(a);
//    mMapDrawer->addPosition(b);
//    mMapDrawer->addPosition(c);
//    mMapDrawer->addPosition(d);
//    mMapDrawer->addPosition(e);
//    mMapDrawer->addPosition(f);


    QList<QGeoCoordinate> qvl;
    qvl.push_back(a);
    qvl.push_back(b);
    qvl.push_back(c);


    QList<QGeoCoordinate> qvl1;
    qvl1.push_back(d);
    qvl1.push_back(e);
    qvl1.push_back(f);




    mMapDrawer->drawPath(5,qvl,"darkblue");
    mMapDrawer->drawPath(6,qvl1,"red");
    mMapDrawer->updatePath(5,1,e);
    mMapDrawer->updatePath(5,0,e);

    QObject::connect(&mMapMouseActionController, &MapMouseActionController::posClickedL_signal, this, &MainController::mouseSignalHandler);






}

void atlas::controller::MainController::mouseSignalHandler(const QGeoCoordinate& coor){


    mMapDrawer->drawCircle(21,coor,"red");
}
