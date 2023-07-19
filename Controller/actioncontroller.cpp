#include "actioncontroller.h"

atlas::controller::ActionController::ActionController(QObject *parent)
    : QObject{parent}
{

}

void atlas::controller::ActionController::ActionHandler()
{

}

void atlas::controller::ActionController::startDrawOptiontoAC(int opt)
{

        emit startDraw_signal(opt);


}

void atlas::controller::ActionController::addEntity(int opt)
{
        emit addEntity_signal(opt);
}

void atlas::controller::ActionController::colorPicker(const QString &clr)
{

        emit color_signal(clr);


}

void atlas::controller::ActionController:: highlight(int Id){
        //qDebug() << Id;

        emit highlight_signal(Id);
}

void atlas::controller::ActionController::highlightEntity(int Id)
{
    emit highlightEntity_signal(Id);
}
void atlas::controller::ActionController:: zoom(double zoomLevel){
    qDebug() << zoomLevel;

    emit zoom_signal(zoomLevel);
}

void atlas::controller::ActionController:: bearing(int brg){

    emit bearing_signal(brg);
}


void atlas::controller::ActionController:: tilt(int tlt){

    emit tilt_signal(tlt);
}

void atlas::controller::ActionController::speed(int spped)
{

    emit speed_signal(spped);
}

void atlas::controller::ActionController::deleteLoc(int mId)
{
        emit deleteLoc_signal(mId);
}

