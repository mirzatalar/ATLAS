#include "mapdrawer.h"
#include "qqmlapplicationengine.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <iostream>


atlas::controller::MapDrawer::MapDrawer(QObject *parent, QQmlApplicationEngine *engine)
    : QObject{parent}
{
    qmlRegisterType<atlas::gui::LineModel>("com.bitessavunma.linemodel", 1, 0, "LineModel");
    engine->rootContext()->setContextProperty("lineModel",  &mLineModel);
    qmlRegisterType<atlas::gui::LineModel>("com.bitessavunma.pathmodel", 1, 0, "PathModel");
    engine->rootContext()->setContextProperty("pathModel",  &mPathModel);
    qmlRegisterType<atlas::gui::LineModel>("com.bitessavunma.circlemodel", 1, 0, "CircleModel");
    engine->rootContext()->setContextProperty("circleModel",  &mCircleModel);
}



//DRAWERS

bool atlas::controller::MapDrawer::drawLine(int mId, const QGeoCoordinate &coordinate1,const QGeoCoordinate &coordinate2,const QString& mColor)
{

    // Some controlss


    return mLineModel.draw( mId, coordinate1, coordinate2, mColor);


}

bool atlas::controller::MapDrawer::drawCircle(int mId, const QGeoCoordinate &mCenter,const QString& mColor)
{

    // Some controlss


    return mCircleModel.draw( mId, mCenter, mColor);


}


//CONTROLLERS

bool atlas::controller::MapDrawer::remove(int mId)

{

    if(mCircleModel.isExist(mId) == true){
        return  mCircleModel.remove(mId);
    }

    else if(mLineModel.isExist(mId) == true){
        return  mLineModel.remove(mId);
    }
    else{
        return false;
    }
}

bool atlas::controller::MapDrawer::move(int mId,const QGeoCoordinate &mPos){

    if(mCircleModel.isExist(mId) == true){
        return  mCircleModel.move(mId,mPos);
    }

    else if(mLineModel.isExist(mId) == true){
        return  mLineModel.move(mId,mPos);
    }
    else{
        return false;
    }
}


//SETTERS

bool atlas::controller::MapDrawer::setHighlight(int mId, bool status){


     if(mCircleModel.isExist(mId) == true){
         return  mCircleModel.setHighlight(mId,status);
     }

     else if(mLineModel.isExist(mId) == true){
         return  mLineModel.setHighlight(mId,status);
     }
     else{
         return false;
     }

}

bool atlas::controller::MapDrawer::setVisibility(int mId, bool status){


     if(mCircleModel.isExist(mId) == true){
         return  mCircleModel.setOpacity(mId,status);
     }

     else if(mLineModel.isExist(mId) == true){
         return  mLineModel.setOpacity(mId,status);
     }
     else{
         return false;
     }

}

bool atlas::controller::MapDrawer::setOpacity(int mId, double mOpacity){


     if(mCircleModel.isExist(mId) == true){
         return  mCircleModel.setOpacity(mId,mOpacity);
     }

     else if(mLineModel.isExist(mId) == true){
         return  mLineModel.setOpacity(mId,mOpacity);
     }
     else{
         return false;
     }

}



bool atlas::controller::MapDrawer::setColor(int mId, const QString& mColor){
     if(mCircleModel.isExist(mId) == true){
         return  mCircleModel.setColor(mId,mColor);
     }

     else if(mLineModel.isExist(mId) == true){
         return  mLineModel.setColor(mId,mColor);
     }
     else{
         return false;
     }
}








void atlas::controller::MapDrawer:: addPosition(const QGeoCoordinate &coordinate){
    return  mPathModel.addPosition( coordinate);
}



