#ifndef CUSTOMENTITYMODEL_H
#define CUSTOMENTITYMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <GUI/models/entity.h>
#include <QGeoCoordinate>


namespace atlas::gui {
class CustomEntityModel : public QAbstractListModel
{
public:
    CustomEntityModel();

   enum EntitiesRole
    {
        Id  = 0,
        Latitude ,
        Longitude,
        Icon ,
        Heading,
        IsHighlited,
        Speed,
        Type,
        ReelIcon,
        TypeName

    };



   bool addEntity( int mId, const EntityType& mType, const QString& mIcon,const  QGeoCoordinate& mCoordinate,  int mHeading,  int mSpeed);
   bool updatePos( int mId, const QGeoCoordinate &newCoordinate);
   bool deleteEntity(int mId);

   // QAbstracListModelInterface
    int rowCount(const QModelIndex &parent) const;
    std::pair<bool, QGeoCoordinate> getCoordinate(int Id) const;
    std::vector<Entity> getEntityList() const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    bool entityExist(int mId);
    bool setHighlight(int mId, bool status);
    bool isHighlighted(int mId);
    QGeoCoordinate getPos(int mId);
    bool isInCoor( int mId, const QGeoCoordinate& m1,const QGeoCoordinate &m2);
    void setSpeed(int mId, int speed);
    int getSpeed(int mId);
    bool isMoving(int mId,bool is);
    bool isMovng;





    QGeoCoordinate midPoint();
private:
    std::vector<Entity> mData;
    QHash<int, QByteArray> mRoleNames;

};
}
#endif // CUSTOMENTITYMODEL_H
