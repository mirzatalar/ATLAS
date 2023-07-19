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
    qmlRegisterType<atlas::gui::PathModel>("com.bitessavunma.pathmodel", 1, 0, "PathModel");
    engine->rootContext()->setContextProperty("pathModel",  &mPathModel);
    qmlRegisterType<atlas::gui::CircleModel>("com.bitessavunma.circlemodel", 1, 0, "CircleModel");
    engine->rootContext()->setContextProperty("circleModel",  &mCircleModel);
    qmlRegisterType<atlas::gui::RectangleModel>("com.bitessavunma.rectanglemodel", 1, 0, "RectangleModel");
    engine->rootContext()->setContextProperty("rectangleModel",  &mRectangleModel);
    qmlRegisterType<atlas::gui::GridModel>("com.bitessavunma.gridmodel", 1, 0, "GridModel");
    engine->rootContext()->setContextProperty("gridModel",  &mGridModel);
    qmlRegisterType<atlas::gui::GridModel>("com.bitessavunma.locationmodel", 1, 0, "LocationModel");
    engine->rootContext()->setContextProperty("locationModel",  &mLocModel);


}



//DRAWERS

bool atlas::controller::MapDrawer::drawLine(int mId, const QGeoCoordinate &coordinate1,const QGeoCoordinate &coordinate2,const QString& mColor)
{
    // Some controlss
    return mLineModel.draw( mId, coordinate1, coordinate2, mColor);
}
bool atlas::controller::MapDrawer::drawRectangle(const QGeoCoordinate &coordinate1,const QGeoCoordinate &coordinate2)
{
    // Some controlss
    return mRectangleModel.draw( coordinate1, coordinate2);
}

bool atlas::controller::MapDrawer::drawCircle(int mId, const QGeoCoordinate &mCenter,const QGeoCoordinate &mCircumCoor,const QString& mColor)
{
    // Some controlss
    return mCircleModel.draw( mId, mCenter,mCircumCoor, mColor);
}

bool atlas::controller::MapDrawer::drawPath(int mId,const QList<QGeoCoordinate>& points,const QString& mColor)
{
    // Some controlss
    return mPathModel.draw( mId, points, mColor);
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
    else if(mPathModel.isExist(mId) == true){
        return  mPathModel.remove(mId);
    }

    else{
        return false;
    }
}

bool atlas::controller::MapDrawer::move(int mId,const QGeoCoordinate &mPos)
{

    if(mCircleModel.isExist(mId) == true){
        return  mCircleModel.move(mId,mPos);
    }

    else if(mLineModel.isExist(mId) == true){
        return  mLineModel.move(mId,mPos);
    }
    else if(mPathModel.isExist(mId) == true){
        return  mPathModel.move(mId,mPos);
    }


    else{
        return false;
    }
}

bool atlas::controller::MapDrawer::moveAll(int count,const QGeoCoordinate &mPos, const QGeoCoordinate &midPoint)
{


    double changeinx = mPos.latitude() - midPoint.latitude();
    double changeiny = mPos.longitude() - midPoint.longitude();
    QGeoCoordinate a(changeinx,changeiny);


    for (int i = 1; i <= count; ++i) {
        if(mCircleModel.isHighlighted(i) == true){
              mCircleModel.move(i,a);
        }

    }
    return true;
}



bool atlas::controller::MapDrawer::updatePath(int mId, bool request,const QGeoCoordinate &coordinate){

    if(mPathModel.isExist(mId) == true){
        if(request == 1){
            return mPathModel.addPoint(mId,coordinate);

        }
        else {
            return mPathModel.removePoint(mId,coordinate);
        }
    }
    else{
        return false;
    }
}



bool  atlas::controller::MapDrawer::removeRec(){
    return mRectangleModel.remove();
}
bool  atlas::controller::MapDrawer::setEndLineR(const QGeoCoordinate &coordinate2){
     return mRectangleModel.setEndl(coordinate2);

}

















//SETTERS

bool atlas::controller::MapDrawer::setEndLine(int mId,const QGeoCoordinate &coordinate2){
    return  mLineModel.setEndLine(mId,coordinate2);
}

bool atlas::controller::MapDrawer::setEndLineC(int mId,const QGeoCoordinate &coordinate2){
    return  mCircleModel.setCircumf(mId,coordinate2);
}


bool atlas::controller::MapDrawer::setBeginLine(int mId,const QGeoCoordinate &coordinate2){
    return  mLineModel.setBeginLine(mId,coordinate2);
}


bool atlas::controller::MapDrawer::setHighlight(int mId, bool status)
{

     if(mCircleModel.isExist(mId) == true){
         return  mCircleModel.setHighlight(mId,status);
     }

     else if(mLineModel.isExist(mId) == true){
         return  mLineModel.setHighlight(mId,status);
     }
     else if(mPathModel.isExist(mId) == true){
         return  mPathModel.setHighlight(mId,status);
     }



     else{
         return false;
     }

}


bool atlas::controller::MapDrawer::setHighlightAll(int count,const QGeoCoordinate &coordinate1, const QGeoCoordinate &coordinate2)
{
     for (int i = 1; i <= count; ++i) {
     if(mCircleModel.isExist(i)){
         if(mCircleModel.isInCoor(i,coordinate1,coordinate2)){
            mCircleModel.setHighlight(i,1);
      }

     }
     }

         return true;


}

QGeoCoordinate atlas::controller::MapDrawer::midPoint()
{
         return mCircleModel.midPoint();
}

bool atlas::controller::MapDrawer::addLoc(int mId, const QGeoCoordinate &coordinate)
{
          mLocModel.add(mId,coordinate);
         return true;
}

bool atlas::controller::MapDrawer::removeLoc(int mId)
{
        mLocModel.del(mId);
        return 1;
}

bool atlas::controller::MapDrawer::setVisibility(int mId, bool status){


     if(mCircleModel.isExist(mId) == true){
         return  mCircleModel.setVisibility(mId,status);
     }

     else if(mLineModel.isExist(mId) == true){
         return  mLineModel.setVisibility(mId,status);
     }
     else if(mPathModel.isExist(mId) == true){
         return  mPathModel.setVisibility(mId,status);
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
     else if(mPathModel.isExist(mId) == true){
         return  mPathModel.setOpacity(mId,mOpacity);
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
     else if(mPathModel.isExist(mId) == true){
         return  mPathModel.setColor(mId,mColor);
     }

     else{
         return false;
     }
}


bool atlas::controller::MapDrawer::isExist(int mId){
     if(mCircleModel.isExist(mId) == true){
         return  1;
     }

     else if(mLineModel.isExist(mId) == true){
         return  1;
     }
     else if(mPathModel.isExist(mId) == true){
         return  1;
     }

     else{
         return false;
     }
}

bool atlas::controller::MapDrawer::createGrid(const QGeoRectangle &rec)
{
     mGridModel.draw(rec);
     return true;
}

void atlas::controller::MapDrawer::clearGrid()
{
     mGridModel.clear();
}

void atlas::controller::MapDrawer::deleteAll(int count)
{
     for (int i = 1; i <= count; ++i) {
         if(mCircleModel.isHighlighted(i) == true){
            mCircleModel.remove(i);
         }

     }
}


