#include "mapcontroller.h"

#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
namespace atlas {
namespace controller {
MapController::MapController(QObject *parent):
    QObject(parent)
{

}

double MapController::zoomLevel() const
{
    return mZoomLevel;
}



void MapController::setZoomLevel(double newZoomLevel)
{
    if (mZoomLevel == newZoomLevel)
        return;
    mZoomLevel = newZoomLevel;
    emit zoomLevelChanged();
}

QGeoCoordinate MapController::center() const
{
    //qDebug() << mCenter;
    return mCenter;
}

void MapController::setCenter(const QGeoCoordinate &newCenter)
{

    if (mCenter == newCenter)
        return;
    mCenter = newCenter;
    emit centerChanged();

}

void MapController::setCenterhelp(const QGeoCoordinate &newCenter){
      //qDebug() <<newCenter;
    QGeoCoordinate x(0,0);
    x.setLatitude(center().latitude() + newCenter.latitude());
    x.setLongitude(center().longitude() + newCenter.longitude());
    //qDebug() << center().latitude() << newCenter.latitude();
    setCenter(x);
}



void MapController::setCenterwithAnim(const QGeoCoordinate &newCenter)
{
    qDebug()<<"Anim start";


    QPropertyAnimation*  animation = new QPropertyAnimation(this, "center");
    animation->setDuration(3000);
    animation->setStartValue(QVariant::fromValue(center()));
    animation->setEndValue(QVariant::fromValue(newCenter));
   // animation->setEasingCurve(QEasingCurve::InOutQuad);


    QPropertyAnimation*  zoomAnim= new  QPropertyAnimation(this, "zoomLevel");
    zoomAnim->setDuration(1500);
    zoomAnim->setStartValue(zoomLevel());
    zoomAnim->setEndValue(6);
    //zoomAnim->setEasingCurve(QEasingCurve::InOutQuad);



    QPropertyAnimation*  zoomAnim2= new  QPropertyAnimation(this, "zoomLevel");
    zoomAnim2->setDuration(1500);
    zoomAnim2->setStartValue(6);
    zoomAnim2->setEndValue(10);
    //zoomAnim2->setEasingCurve(QEasingCurve::InOutQuad);




    connect(zoomAnim,&QPropertyAnimation::finished,this,[zoomAnim2](){
        zoomAnim2->start(QPropertyAnimation::DeleteWhenStopped);
    });


    animation->start(QPropertyAnimation::DeleteWhenStopped);
    zoomAnim->start(QPropertyAnimation::DeleteWhenStopped);

//    mTimer = new QTimer();

//    mTimer->start(100);
    static bool tick = 0; // Sayaç değeri
    static int countr = 0;
    static bool stop = 0;


//    QObject :: connect(mTimer,&QTimer::timeout,[this, &newCenter]{
//        qDebug() << zoomLevel();


//        if(zoomLevel() > 1 && tick == false && stop == false){
//            setZoomLevel(zoomLevel()-(1));

//        }

//        if(zoomLevel() == 6 && tick == false){

//            tick = 1;
//        }

//        if(mZoomLevel < 10 && tick == true && stop != 1 && countr > 40){
//            setZoomLevel(zoomLevel()+(1));
//        }
//        if(mZoomLevel == 14){
//              stop = 1;
//        }

//        double changeinx = newCenter.latitude() - center().latitude();
//        double changeiny = newCenter.longitude() - center().longitude();


//        QGeoCoordinate a(changeinx/(20),changeiny/(20));

//        setCenterhelp(a);




//        ++countr;
//        if (countr > (50)) {
//              mTimer->stop();
//              countr = 0;
//        }





//    });

 //   emit centerChanged();
}

int MapController::bearing() const
{
    return mBearing;
}

void MapController::setBearing(int newBearing)
{
    if (mBearing == newBearing)
        return;
    mBearing = newBearing;
    emit bearingChanged();
}

int MapController::tilt() const
{
    return mTilt;
}

void MapController::setTilt(int newTilt)
{
    if (mTilt == newTilt)
        return;
    mTilt = newTilt;
    emit tiltChanged();
}

}
}
