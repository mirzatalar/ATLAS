#include "maincontroller.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtPositioning>
#include <iostream>
#include <Controller/mapdrawer.h>
#include <csignal>
#include <QtPositioning>

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
    ctx->setContextProperty("actionController",&mActionController);


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


 //mMapDrawer->drawLine(18,b,a,"red");
//    mMapDrawer->drawLine(19,b,e,"black");
//    mMapDrawer->drawCircle(25, mMapMouseActionController.tester,"pink");
//        mMapDrawer->drawCircle(26,a,b,"blue");
//        mMapDrawer->drawCircle(26,e,f,"red");

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




    //    mMapDrawer->drawPath(5,qvl,"darkblue");
    //    mMapDrawer->drawPath(6,qvl1,"red");
    //    mMapDrawer->updatePath(5,1,e);
    //    mMapDrawer->updatePath(5,0,e);

    QObject::connect(&mMapMouseActionController, &MapMouseActionController::posClickedL_signal, this, &MainController::setBeginLine);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::posClickedR_signal, this, &MainController::endDraw);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::pos_signal, this, &MainController::setEndLine);
    QObject::connect(&mActionController, &ActionController::startDraw_signal, this, &MainController::startDraw);



}

void atlas::controller::MainController::setBeginLine(const QGeoCoordinate& coor){

if(start == 1 && end==0 && rightclicked == 0){
        if(option == 1){
            int id = 1;
            while(mMapDrawer->isExist(id)){
                id++;
            }
            mMapDrawer->drawLine(id,coor,coor,"red");
            start = 0;
             end = 0;
        }
        else if(option == 2){
             int id = 1;
             while(mMapDrawer->isExist(id)){
                id++;
             }
             mMapDrawer->drawCircle(id,coor,coor,"red");
             start = 0;
             end = 0;
        }
        rightclicked = 1;
    }
    else if(start == 0 && end==0 && rightclicked == 1){
        if(option == 1){
             int id = 1;
             while(mMapDrawer->isExist(id)){
                id++;
             }
             mMapDrawer->setEndLine(id-1,coor);
             end = 1;
             start = 0;
        }
        else  if(option == 2){
             int id = 1;
             while(mMapDrawer->isExist(id)){
                id++;
             }
             mMapDrawer->setEndLineC(id-1,coor);
             end = 1;
             start = 0;
        }
        rightclicked = 0;
}
}

void atlas::controller::MainController::setEndLine(const QGeoCoordinate& coor){

    if(start == 0 && end == 0){
        if(option == 1){
            int id = 1;
            while(mMapDrawer->isExist(id)){
                id++;

            }
            //qDebug() << id;
            mMapDrawer->setEndLine(id - 1,coor);
        }
        else if(option == 2){
            int id = 1;
            while(mMapDrawer->isExist(id)){
                id++;

            }
            //qDebug() << id;
            mMapDrawer->setEndLineC(id - 1,coor);
        }
    }

}


void atlas::controller::MainController::endDraw(const QGeoCoordinate& coor){

    if(start == 0 && end==0){
        if(option == 1){
            int id = 1;
            while(mMapDrawer->isExist(id)){
                id++;
            }
            mMapDrawer->remove(id-1);
            end = 1;
            start = 0;
             }
         else  if(option == 2){
            int id = 1;
            while(mMapDrawer->isExist(id)){
                id++;
            }
            mMapDrawer->remove(id-1);
            end = 1;
            start = 0;
        }
         }
    rightclicked = 0;
    }






void atlas::controller::MainController::startDraw(int opt){
    option = opt;
    if(start == 0 && end == 1){
        start = 1;
        end = 0;
    }
}
