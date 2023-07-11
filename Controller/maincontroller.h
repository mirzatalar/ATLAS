#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <Controller/mapcontroller.h>

class QQmlApplicationEngine;


namespace atlas::controller{
class  MapDrawer;

    class MainController : public QObject
    {
    public:
        MainController(QObject *parent = nullptr);

        void init(QQmlApplicationEngine* engine);
    private:
        MapController mMapController;
        MapDrawer*   mMapDrawer;


    };
}
#endif // MAINCONTROLLER_H
