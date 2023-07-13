#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <QObject>
#include <QGeoCoordinate>
#include <Controller/mapmouseactioncontroller.h>

namespace atlas::controller{
    class ActionController : public QObject
    {
        Q_OBJECT
    public:
        explicit ActionController(QObject *parent = nullptr);
        void ActionHandler();


    private:
        MapMouseActionController mMapMouseActionController;


    signals:
           void startDraw_signal(int opt);


    public slots :
            void startDrawOptiontoAC(int opt);

    };
}
#endif // ACTIONCONTROLLER_H
