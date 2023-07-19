#include "mapmouseactioncontroller.h"
#include <QDebug>

atlas::controller::MapMouseActionController::MapMouseActionController(QObject *parent)
    : QObject{parent}
{

}



void atlas::controller::MapMouseActionController::toCPPpos(const QGeoCoordinate &mCoordinate){

    //qDebug() << "current pos x: " << mCoordinate ;
    emit pos_signal(mCoordinate);


}

void atlas::controller::MapMouseActionController::toCPPposClickedL(const QGeoCoordinate &mCoordinate){

    //qDebug() << "left clicked x: " << mCoordinate ;
    //tester = mCoordinate;
    emit startDrawLine_signal(mCoordinate);
    emit posClickedL_signal(mCoordinate);

}


void atlas::controller::MapMouseActionController::toCPPposClickedR(const QGeoCoordinate &mCoordinate){

    //qDebug() << "right clicked x: " << mCoordinate ;
    emit posClickedR_signal(mCoordinate);

}


void atlas::controller::MapMouseActionController::toCPPposClickedD(const QGeoCoordinate &mCoordinate){

   // qDebug() << "double clicked x: " << mCoordinate ;
    emit posClickedD_signal(mCoordinate);

}

void atlas::controller::MapMouseActionController:: currentRec(const QGeoRectangle &rectangle){
    emit currentRec_signal(rectangle);
}

void atlas::controller::MapMouseActionController::cntr(const QGeoCoordinate &coordinate1)
{

    emit center_signal(coordinate1);
}

void atlas::controller::MapMouseActionController::gocntr()
{

    emit gocenter_signal();
}
