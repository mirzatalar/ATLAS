#include "mapmouseactioncontroller.h"

atlas::controller::MapMouseActionController::MapMouseActionController(QObject *parent)
    : QObject{parent}
{

}



void atlas::controller::MapMouseActionController::toCPPpos(const QGeoCoordinate &mCoordinate){

    //qDebug() << "current pos x: " << mCoordinate ;


}

void atlas::controller::MapMouseActionController::toCPPposClickedL(const QGeoCoordinate &mCoordinate){

    qDebug() << "left clicked x: " << mCoordinate ;
    //tester = mCoordinate;

    emit posClickedL_signal(mCoordinate);
}


void atlas::controller::MapMouseActionController::toCPPposClickedR(const QGeoCoordinate &mCoordinate){

    //qDebug() << "right clicked x: " << mCoordinate ;

}


void atlas::controller::MapMouseActionController::toCPPposClickedD(const QGeoCoordinate &mCoordinate){

    //qDebug() << "double clicked x: " << mCoordinate ;

}

