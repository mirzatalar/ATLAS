#include "actioncontroller.h"

atlas::controller::ActionController::ActionController(QObject *parent)
    : QObject{parent}
{

}

void atlas::controller::ActionController::ActionHandler()
{

}

void atlas::controller::ActionController::startDrawLinetoAC()
{

    qDebug() << "AC WORKING";
    emit startDrawLine_signal();
}
