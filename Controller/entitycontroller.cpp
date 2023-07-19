#include "entitycontroller.h"
#include "qqmlapplicationengine.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QTimer>
#include <QPropertyAnimation>

atlas::controller::EntityController::EntityController(QObject *parent, QQmlApplicationEngine *engine)
    : QObject{parent}
{
    qmlRegisterType<atlas::gui::CustomEntityModel>("com.bitessavunma.customentitymodel", 1, 0, "CustomEntityModel");
    engine->rootContext()->setContextProperty("customEntityModel",  &mCustomEntityModel);

    mTypetoIcon[EntityType :: CIVIL_CAR] = "qrc:/icons/icon_civil_car.png";
    mTypetoIcon[EntityType :: AIRCRAFT] = "qrc:/icons/icon_aircraft.png";
    mTypetoIcon[EntityType :: DRONE] = "qrc:/icons/icon_drone.png";
    mTypetoIcon[EntityType :: TANK] = "qrc:/icons/icon_tank.png";
    mTypetoIcon[EntityType :: HELICOPTER] = "qrc:/icons/icon_helicopter.png";
    mTypetoIcon[EntityType :: WARSHIP] = "qrc:/icons/icon_warship.png";
}

bool atlas::controller::EntityController:: addEntity( int mId,const  EntityType& mType,const  QGeoCoordinate& mCoordinate,  int mHeading,  int mSpeed)
{

    // Some controlss
    entityCount++;
    QString mIcon = mTypetoIcon[mType];
    return mCustomEntityModel.addEntity(mId, mType,mIcon,mCoordinate,mHeading-90,mSpeed);
}

bool  atlas::controller::EntityController:: updatePos( int mId, const QGeoCoordinate& newCoordinate)
{
    // Some Controls..

//    if( newCoordinate == mCustomEntityModel.getPos(mId)){
//        qDebug() << "buraya girdi";
//        QGeoCoordinate x ;
//        x.setLatitude(0);
//        x.setLongitude(0);
//        return mCustomEntityModel.updatePos(mId,x);
//        }


    return  mCustomEntityModel.updatePos(mId,newCoordinate);
}





bool  atlas::controller::EntityController::  deleteentity(int mId)
{
    // Some Controlss..
    entityCount--;
    return  mCustomEntityModel.deleteEntity(mId);
}

bool atlas::controller::EntityController::setHighlight(int mId, bool status)
{
    //qDebug() << status;
    if(mCustomEntityModel.entityExist(mId) == true) {
        return mCustomEntityModel.setHighlight(mId,status);
    }
}

bool atlas::controller::EntityController::isHighlighted(int mId)
{
    return mCustomEntityModel.isHighlighted(mId);
}

void atlas::controller::EntityController::deleteAll(int count)
{
    for (int i = 1; i <= count; ++i) {
        if(mCustomEntityModel.isHighlighted(i) == true){
            mCustomEntityModel.deleteEntity(i);
            entityCount--;
        }

    }
}

QGeoCoordinate atlas::controller::EntityController::getPos(int mId)
{
    return mCustomEntityModel.getPos(mId);
}

QGeoCoordinate atlas::controller::EntityController::midPoint()
{
    return mCustomEntityModel.midPoint();
}

bool atlas::controller::EntityController::moveAll(int count, const QGeoCoordinate &mPos, const QGeoCoordinate &midPoint,MapController &mc,bool mapMove)
{
//qDebug() << "cagrildi";
//    double changeinx = mPos.latitude() - midPoint.latitude();
//    double changeiny = mPos.longitude() - midPoint.longitude();
//    QGeoCoordinate a(changeinx,changeiny);

//   // qDebug() << a;


//    for (int i = 1; i <= count; ++i) {
//        if(mCustomEntityModel.isHighlighted(i) == true){
//            mCustomEntityModel.updatePos(i,a);
//        }

//    }
//    return true;

    //    QPropertyAnimation*  animation = new QPropertyAnimation(this, "mCoordianate");
    //    animation->setDuration(10000);
    //    animation->setStartValue(QVariant::fromValue(center()));
    //    animation->setEndValue(QVariant::fromValue(mPos));





    if(count != 0) {
        mTimer = new QTimer();

        //mTimer->setSingleShot(true); // Tek seferlik tetikleme modunu etkinleştirin
        mTimer->start(10);
        static int counter = 0; // Sayaç değeri



        QObject :: connect(mTimer,&QTimer::timeout,[this, count, mPos, midPoint,&mc, mapMove]{





            double changeinx = mPos.latitude() - midPoint.latitude();
            double changeiny = mPos.longitude() - midPoint.longitude();

            if(mapMove == true) {

                mc.setCenter(mCustomEntityModel.midPoint());
            }

            for (int i = 1; i <= count; ++i) {
                //qDebug() << mCustomEntityModel.getSpeed(i);
                QGeoCoordinate a(changeinx/(800/mCustomEntityModel.getSpeed(i)),changeiny/(800/mCustomEntityModel.getSpeed(i)));
                if(mCustomEntityModel.isHighlighted(i) == true){
                    mCustomEntityModel.updatePos(i,a);
                }


            }
            ++counter;
            if (counter >= (800/mCustomEntityModel.getSpeed(1))) {
                mTimer->stop();
                counter = 0;
            }



        });
    }


//    for (int i = 1; i <= count; ++i) {
//        if(mCustomEntityModel.isHighlighted(i) == true){
//            mCustomEntityModel.updatePos(i,a);
//        }

//    }
    return true;
}

bool atlas::controller::EntityController::setHighlightAll(int count,const QGeoCoordinate &coordinate1, const QGeoCoordinate &coordinate2)
{
    for (int i = 1; i <= count; ++i) {
        if(mCustomEntityModel.entityExist(i)){
            if(mCustomEntityModel.isInCoor(i,coordinate1,coordinate2)){
                mCustomEntityModel.setHighlight(i,1);
            }

        }
    }

    return true;


}

void atlas::controller::EntityController::setSpeed(int entitycount,int speed)
{
    for (int i = 1; i <= entitycount; ++i) {
        if(mCustomEntityModel.isHighlighted(i) == true){
            mCustomEntityModel.setSpeed(i,speed);
        }
    }
}

int atlas::controller::EntityController::getSpeed(int id)
{
    return mCustomEntityModel.getSpeed(id);
}
