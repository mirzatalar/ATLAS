#ifndef MAPMOUSEACTIONCONTROLLER_H
#define MAPMOUSEACTIONCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QGeoCoordinate>

namespace  atlas :: controller
{

    class MapMouseActionController : public QObject
    {
        Q_OBJECT
    public:
        explicit MapMouseActionController(QObject *parent = nullptr);

        QGeoCoordinate tester;

    signals:
        void pos_signal(const QGeoCoordinate &mCoordinate);
        void posClickedR_signal(const QGeoCoordinate &mCoordinate);
        void posClickedL_signal(const QGeoCoordinate &mCoordinate);
        void posClickedD_signal(const QGeoCoordinate &mCoordinate);
        void startDrawLine_signal(const QGeoCoordinate &coordinate1);


    public slots :
        void toCPPpos(const QGeoCoordinate &mCoordinate);
        void toCPPposClickedR(const QGeoCoordinate &mCoordinate);
        void toCPPposClickedL(const QGeoCoordinate &mCoordinate);
        void toCPPposClickedD(const QGeoCoordinate &mCoordinate);
        //QGeoCoordinate option(int opt);

    };
}
#endif // MAPMOUSEACTIONCONTROLLER_H
