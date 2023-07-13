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
           void startDrawLine_signal();

    public slots :
            void startDrawLinetoAC();

    };
}
#endif // ACTIONCONTROLLER_H
