#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include <QObject>
#include <QGeoCoordinate>
#include "GUI/models/customentitymodel.h"
#include "qqmlapplicationengine.h"
#include <QQmlEngine>
namespace  atlas :: controller
{
    class EntityController : public QObject
    {
        Q_OBJECT
    public:
        explicit EntityController(QObject *parent, QQmlApplicationEngine *eng);
        bool addEntity( int mId, const EntityType& mType,const  QGeoCoordinate& mCoordinate,  int mHeading,  int mSpeed);
        bool updatePos( int mId, const QGeoCoordinate &newCoordinate);
        bool deleteentity(int mId);
        bool setHighlight(int mId, bool status);
        bool isHighlighted(int mId);
        bool isExist(int mId);
        QGeoCoordinate midPoint();
        bool moveAll(int count,const QGeoCoordinate &mPos,const QGeoCoordinate &midPoint);
        void deleteAll(int count);
        QGeoCoordinate getPos(int mId);
        bool setHighlightAll(int count,const QGeoCoordinate &coordinate1, const QGeoCoordinate &coordinate2);


    private:
        atlas::gui::CustomEntityModel mCustomEntityModel;
        std::map<EntityType,QString> mTypetoIcon;
        int entityCount = 0;
        QTimer *mTimer;


    };
}
#endif // ENTITYCONTROLLER_H
