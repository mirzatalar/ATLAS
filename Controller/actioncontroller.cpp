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
