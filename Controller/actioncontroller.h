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
           void color_signal(const QString &clr);
           void highlight_signal(int Id);
           void highlightEntity_signal(int Id);
           void zoom_signal(int zoomlevel);
           void bearing_signal(int brg);
           void tilt_signal(int tlt);
           void addEntity_signal(int opt);


    public slots :
            void startDrawOptiontoAC(int opt);
            void addEntity(int opt);
            void colorPicker(const QString &clr);
            void highlight(int Id);
            void highlightEntity(int Id);
            void zoom(int zoomlevel);
            void bearing(int brg);
            void tilt(int tlt);


    };
}
#endif // ACTIONCONTROLLER_H
