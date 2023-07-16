#include "mapcontroller.h"


namespace atlas {
namespace controller {
MapController::MapController(QObject *parent):
    QObject(parent)
{

}

int MapController::zoomLevel() const
{
    return mZoomLevel;
}



void MapController::setZoomLevel(int newZoomLevel)
{
    if (mZoomLevel == newZoomLevel)
        return;
    mZoomLevel = newZoomLevel;
    emit zoomLevelChanged();
}

QGeoCoordinate MapController::center() const
{
    return mCenter;
}

void MapController::setCenter(const QGeoCoordinate &newCenter)
{

    mCenter = newCenter;
    emit centerChanged();
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
