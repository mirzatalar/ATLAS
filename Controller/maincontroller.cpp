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
    mMapController.setZoomLevel(13);
    mMapController.setCenter(a);
    mMapController.setTilt(0);
    mMapController.setBearing(0);




    //TESTS
    mMapDrawer = new MapDrawer(nullptr,engine);
    mEntityController = new EntityController(nullptr,engine);
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
    QObject::connect(&mActionController, &ActionController::highlightEntity_signal, this, &MainController::highlightEntity);
    QObject::connect(&mActionController, &ActionController::zoom_signal, this, &MainController::setZoom);
    QObject::connect(&mActionController, &ActionController::bearing_signal, this, &MainController::setBearing);
    QObject::connect(&mActionController, &ActionController::tilt_signal, this, &MainController::setTilt);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::currentRec_signal, this, &MainController::grid);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::center_signal, this, &MainController::center);
    QObject::connect(&mMapMouseActionController, &MapMouseActionController::gocenter_signal, this, &MainController::gocenter);

    QObject::connect(&mActionController, &ActionController::addEntity_signal, this, &MainController::addEntity);
    QObject::connect(&mActionController, &ActionController::speed_signal, this, &MainController::setSpeed);
     QObject::connect(&mActionController, &ActionController::deleteLoc_signal, this, &MainController::deleteLoc);





}

void atlas::controller::MainController::LeftClicked(const QGeoCoordinate& coor){

//qDebug() << option;
//qDebug() << start;
//qDebug() << end;

    if(option == 0){
        for (int var = 1; var <= itemCount; ++var) {
            mMapDrawer->setHighlight(var,0);
        }
    }
    if(addedItem == 0 && option != 4){
        for (int var = 1; var <= entityCount; ++var) {
            mEntityController->setHighlight(var,0);
        }
    }

     if(option == 4){


        QGeoCoordinate x = mEntityController->midPoint();
         entityCount = mEntityController->entityCount;




        mEntityController->moveAll(entityCount,coor, x,mMapController,mapMove);
        for (int i = 1; i <= itemCount; ++i) {
            mMapDrawer->setHighlight(i,0);
        }



        start = 0;
        end = 1;
        QGuiApplication::restoreOverrideCursor();
        option = 0;


    }

if( option == 7){
    QGuiApplication::restoreOverrideCursor();
    cntr = coor;
    end = 1;
    start = 0;

}
else if(addedItem != 0){
    QGuiApplication::restoreOverrideCursor();
    mEntityController->addEntity(++entityCount,(EntityType)addedItem,coor,90,20);
    start = 0;
    end = 1;
    addedItem = 0;

}

else if(option == 10){
    QGuiApplication::restoreOverrideCursor();
    mMapDrawer->addLoc(++locCount, coor);
    start = 0;
    end = 1;
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
    qDebug() << "acc";
             QGuiApplication::restoreOverrideCursor();
        if(option == 1){

             mMapDrawer->setEndLine(itemCount,coor);
             end = 1;
             start = 0;
             option = 0;
        }
        else  if(option == 2){

             mMapDrawer->setEndLineC(itemCount,coor);
             end = 1;
             start = 0;
             option = 0;
        }

        else  if(option == 5){

             mMapDrawer->removeRec();
             bottomRight = coor;
             mMapDrawer->setHighlightAll(entityCount,topLeft,bottomRight);
             mEntityController->setHighlightAll(entityCount,topLeft,bottomRight);
             end = 1;
             start = 0;
             option = 0;
        }
        else  if(option == 4){

             end = 1;
             start = 0;
             option = 0;

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
//    if(option == 4){

////        QGeoCoordinate x = mMapDrawer->midPoint();


////        mMapDrawer->moveAll(itemCount,coor, x);

//                QGeoCoordinate x = mEntityController->midPoint();




//                mEntityController->moveAll(entityCount,coor, x);

//    }


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
    if(start == 0 && end == 1 ){
        start = 1;
        end = 0;
    }
    if(option == 6)
    {
        gridOn = !gridOn;
        start = 0;
        end = 1;
    }
    if(option == 6 && !gridOn)
    {
        mMapDrawer->clearGrid();
    }
    if(option == 7 || option == 10)
    {
       QGuiApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
    }

    if(option ==8){
       mMapDrawer->deleteAll(itemCount);

       mEntityController->deleteAll(entityCount);
       start = 0;
       end = 1;

    }
    if(option == 9){

       mapMove = !mapMove;

       start = 0;
       end = 1;
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
    //qDebug() << id;
    mMapDrawer->setHighlight(id,1);

}

void atlas::controller::MainController::highlightEntity(int id){



     mEntityController->setHighlight(id,!mEntityController->isHighlighted(id));
}

void atlas::controller::MainController::setZoom(double zoomLevel){
     qDebug() << zoomLevel;
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
    }
}

void atlas::controller::MainController::center(const QGeoCoordinate &coor)
{
    mMapController.setCenterwithAnim(coor);
}

void atlas::controller::MainController::gocenter()
{

    mMapController.setCenterwithAnim(cntr);
}

void atlas::controller::MainController::addEntity(int opt)
{
    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
    if(start == 0 && end == 1){
        start = 1;
        end = 0;
    }
    addedItem = opt;
}

void atlas::controller::MainController::deleteLoc(int mId)
{
    mMapDrawer->removeLoc(mId);
}

void atlas::controller::MainController::setSpeed(int speed)
{

    mEntityController->setSpeed(entityCount,speed);
}
