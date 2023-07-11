#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H
#include <QObject>
#include <QGeoCoordinate>

namespace  atlas :: controller
{

    class MapController : public QObject
    {
        Q_OBJECT
    public:
        MapController(QObject* parent=nullptr);

        int zoomLevel() const;

        void setZoomLevel(int newZoomLevel);

        QGeoCoordinate center() const;
        void setCenter(const QGeoCoordinate &newCenter);

        int bearing() const;
        void setBearing(int newBearing);

        int tilt() const;
        void setTilt(int newTilt);

    signals:
        void zoomLevelChanged();

        void centerChanged();

        void bearingChanged();

        void tiltChanged();

    private:
        int mZoomLevel;
        QGeoCoordinate mCenter;
        int mBearing;
        int mTilt;
        Q_PROPERTY(int zoomLevel READ zoomLevel WRITE setZoomLevel NOTIFY zoomLevelChanged)
        Q_PROPERTY(QGeoCoordinate center READ center WRITE setCenter NOTIFY centerChanged)
        Q_PROPERTY(int bearing READ bearing WRITE setBearing NOTIFY bearingChanged)
        Q_PROPERTY(int tilt READ tilt WRITE setTilt NOTIFY tiltChanged)
    };
}
#endif // MAPCONTROLLER_H
