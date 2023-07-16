#include "maincontroller.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>
#include <QtPositioning>
#include <iostream>
#include <Controller/mapdrawer.h>
#include <csignal>
#include <QtPositioning>
#include <QCursor>

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
    a.setLongitude(36);
    mMapController.setZoomLevel(6);
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

    QObject::connect(&mMapMouseActionController, &MapMouseActionController::posClickedL_signal, this, &MainController::LeftClicked);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::posClickedR_signal, this, &MainController::RightClicked);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::posClickedD_signal, this, &MainController::DoubleClicked);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::pos_signal, this, &MainController::Position);
    QObject::connect(&mActionController, &ActionController::startDraw_signal, this, &MainController::StartAction);
    QObject::connect(&mActionController, &ActionController::color_signal, this, &MainController::ChangeColor);
    QObject::connect(&mActionController, &ActionController::highlight_signal, this, &MainController::highlight);
    QObject::connect(&mActionController, &ActionController::zoom_signal, this, &MainController::setZoom);
    QObject::connect(&mActionController, &ActionController::bearing_signal, this, &MainController::setBearing);
    QObject::connect(&mActionController, &ActionController::tilt_signal, this, &MainController::setTilt);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::currentRec_signal, this, &MainController::grid);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::center_signal, this, &MainController::center);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::gocenter_signal, this, &MainController::gocenter);




}

void atlas::controller::MainController::LeftClicked(const QGeoCoordinate& coor){





if(option == 4){
        QGeoCoordinate x = mMapDrawer->midPoint();


    mMapDrawer->moveAll(itemCount,coor, x);
    for (int i = 1; i <= itemCount; ++i) {
        mMapDrawer->setHighlight(i,0);
    }
}

if( option == 7){
    QGuiApplication::restoreOverrideCursor();
    cntr = coor;
    end = 1;
    start = 0;
    option =  0;
}



else if(start == 1 && end==0 && rightclicked == 0){

QGuiApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
        if(option == 1){

            mMapDrawer->drawLine(++itemCount,coor,coor,clor);
            start = 0;
             end = 0;
        }
        else if(option == 2){

             mMapDrawer->drawCircle(++itemCount,coor,coor,clor);
             start = 0;
             end = 0;
        }
        else if(option == 3){

             QList<QGeoCoordinate> qvl1 = {coor};
             mMapDrawer->drawPath(++itemCount,qvl1,clor);
             start = 0;
             end = 0;
        }

        else if(option == 5){

             mMapDrawer->drawRectangle(coor,coor);
             topLeft = coor;
             start = 0;
             end = 0;
        }

        rightclicked = 1;

    }
    else if(start == 0 && end==0 && rightclicked == 1){
             QGuiApplication::restoreOverrideCursor();
        if(option == 1){

             mMapDrawer->setEndLine(itemCount,coor);
             end = 1;
             start = 0;
        }
        else  if(option == 2){

             mMapDrawer->setEndLineC(itemCount,coor);
             end = 1;
             start = 0;
        }

        else  if(option == 5){

             mMapDrawer->removeRec();
             bottomRight = coor;
             mMapDrawer->setHighlightAll(itemCount,topLeft,bottomRight);
             end = 1;
             start = 0;
        }

        rightclicked = 0;
}
    if(option == 3 && end == 0 && start == 0){
        mMapDrawer->updatePath(itemCount,1,coor);
        end = 0;
        start = 0;
    }
}

void atlas::controller::MainController::Position(const QGeoCoordinate& coor){





    if(start == 0 && end == 0){
        if(option == 1){
            mMapDrawer->setEndLine(itemCount,coor);
        }
        else if(option == 2){
            mMapDrawer->setEndLineC(itemCount,coor);
        }
        else if(option == 5){
            mMapDrawer->setEndLineR(coor);
        }


    }


}


void atlas::controller::MainController::RightClicked(const QGeoCoordinate& coor){

    if(start == 0 && end==0){
         QGuiApplication::restoreOverrideCursor();
        if(option == 1){
            mMapDrawer->remove(itemCount);
            end = 1;
            start = 0;
             }
         else  if(option == 2){
            mMapDrawer->remove(itemCount);
            end = 1;
            start = 0;
        }
        else  if(option == 3){
            end = 1;
            start = 0;
             }

         }
    rightclicked = 0;
    }


void atlas::controller::MainController::ChangeColor(const QString &clr){
    clor = clr;
    //qDebug() << clor;
}




void atlas::controller::MainController::StartAction(int opt){
    option = opt;
    if(start == 0 && end == 1){
        start = 1;
        end = 0;
    }
    if(option == 6)
    {
        gridOn = !gridOn;
    }
    if(option == 6 && !gridOn)
    {
        mMapDrawer->clearGrid();
    }
    if(option == 7)
    {
       QGuiApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
    }

}


void atlas::controller::MainController::DoubleClicked(const QGeoCoordinate& coor){

    if(option == 3){
        mMapDrawer->remove(itemCount);
        end = 1;
        start = 0;
        option = 0;
        QGuiApplication::restoreOverrideCursor();
    }
}

void atlas::controller::MainController::highlight(int id){
    mMapDrawer->setHighlight(id,1);
}

void atlas::controller::MainController::setZoom(int zoomLevel){
    mMapController.setZoomLevel(zoomLevel);
}
void atlas::controller::MainController::setTilt(int tlt){
    mMapController.setTilt(tlt);
}
void atlas::controller::MainController::setBearing(int brg){
    mMapController.setBearing(brg);
}


void atlas::controller::MainController::grid(const QGeoRectangle &rec){

    if(gridOn == true){

        mMapDrawer->createGrid(rec);

//        mMapDrawer->remove(500);

//        double a = rec.topLeft().longitude(); // 22
//        double b = rec.topRight().longitude(); // 48
//        double c = rec.bottomRight().latitude(); // 34
//        double d = rec.topRight().latitude(); //45

//        double ennumber = abs(rec.bottomLeft().latitude() - rec.topLeft().latitude()) ;
//        double boynumber =abs(rec.bottomLeft().longitude() - rec.topRight().longitude()) ;

//        for (int i = 1; i <= ennumber; ++i) {
//            mMapDrawer->drawLine(500,QGeoCoordinate(c + i*(d-c)/ennumber,a), QGeoCoordinate(c + i*(d-c)/ennumber,b+1),"white");
//        }

//        for (int i = 1; i <= boynumber; ++i) {
//            mMapDrawer->drawLine(500,QGeoCoordinate(c-1,a + i*(b-a)/boynumber), QGeoCoordinate(d+1,a + i*(b-a)/boynumber),"white");
//        }
//        mMapDrawer->setOpacity(500,0.4);

    }



}

void atlas::controller::MainController::center(const QGeoCoordinate &coor)
{

    cntr = coor;

}

void atlas::controller::MainController::gocenter()
{

    mMapController.setCenter(cntr);
}
