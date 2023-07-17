#include "customentitymodel.h"
#include <iostream>
#include <QDebug>

atlas::gui::CustomEntityModel::CustomEntityModel()
{
    mRoleNames[Id] = "Id" ;
    mRoleNames[Latitude] = "latitude";
    mRoleNames[Longitude] = "longitude";
    mRoleNames[Icon] = "icon";
    mRoleNames[Heading] = "heading";
    mRoleNames[Speed] = "Speed";
    mRoleNames[Type] = "Type";
    mRoleNames[IsHighlited] = "ishighlited";
}

bool atlas::gui::CustomEntityModel::addEntity(int mId, const EntityType &mType, const QString &mIcon, const QGeoCoordinate &mCoordinate, int mHeading, int mSpeed)
{

        if(entityExist(mId) == true){
        std::cout << "Entity " << mId <<  " already exists" << std::endl;
                return false;
        }


        else {

                beginResetModel();



            Entity newEntity(mId, mType, mCoordinate, mHeading, mSpeed);
            newEntity.mIcon = mIcon;
            if(mType == (EntityType)1){
                newEntity.highlitedIcon = "qrc:/icons/h-car.png";
            }
            if(mType == (EntityType)2){
                newEntity.highlitedIcon = "qrc:/icons/h-aircraft.png";
            }
            if(mType == (EntityType)3){
                newEntity.highlitedIcon = "qrc:/icons/h-drone.png";
            }
            if(mType == (EntityType)4){
                newEntity.highlitedIcon = "qrc:/icons/h-tank.png";
            }
            if(mType == (EntityType)5){
                newEntity.highlitedIcon = "qrc:/icons/h-helicopter.png";
            }
            if(mType == (EntityType)6){
                newEntity.highlitedIcon = "qrc:/icons/h-warship.png";
            }

            newEntity.mIsHighlited = false;
            mData.push_back(newEntity);
            std::cout << "Entity " << mId << " has been added" << std::endl;

            endResetModel();

            return true;
        }
}

bool atlas::gui:: CustomEntityModel::updatePos(int mId, const QGeoCoordinate &newCoordinate)
{

    auto returned = [mId](const Entity& entity){return entity.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);


    if(it != mData.end()){

                QVector<int> roles = {Latitude, Longitude, Heading};
                    beginResetModel();


                  if( newCoordinate.latitude() < 0){
                       it->mHeading = (180.0/3.141592653589793238463)*atan(newCoordinate.longitude()/newCoordinate.latitude()) + 90;
                 }
                  else{
                    it->mHeading = (180.0/3.141592653589793238463)*atan(newCoordinate.longitude()/newCoordinate.latitude()) - 90;
                 }

                it->mCoordinate.setLatitude(it->mCoordinate.latitude() + newCoordinate.latitude());
                it->mCoordinate.setLongitude(it->mCoordinate.longitude() + newCoordinate.longitude());
                endResetModel();


        return true;
    }

    return false;
}

bool atlas::gui:: CustomEntityModel::deleteEntity(int mId)
{

    auto isremoved = [mId](const Entity& entity){return entity.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),isremoved);

    beginResetModel();

    mData.erase(itr,itr+1);
    endResetModel();

    return true;

}

bool atlas::gui::CustomEntityModel::isInCoor( int mId, const QGeoCoordinate& m1,const QGeoCoordinate &m2){


    auto isremoved = [mId](const Entity& entity){return entity.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),isremoved);

    if(itr != mData.end()){

        if(itr->mCoordinate.latitude() <= m1.latitude() && itr->mCoordinate.latitude() >= m2.latitude() && itr->mCoordinate.longitude() >= m1.longitude() && itr->mCoordinate.longitude() <= m2.longitude()){

                    return true;
        }
        else{

                    return false;
        }
    }



}

int atlas::gui::CustomEntityModel::rowCount(const QModelIndex &parent) const
{
    return mData.size();
}

std::pair<bool, QGeoCoordinate>atlas::gui::CustomEntityModel::getCoordinate(int mId) const
{
    auto returned = [mId](const Entity& entity){return entity.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),returned);

    if(itr == mData.end()){
        return std::make_pair(false, QGeoCoordinate{});
    }

    return std::make_pair(true, itr->mCoordinate);
}


  std::vector<Entity> atlas::gui::CustomEntityModel:: getEntityList() const
{
    std::vector<Entity> returnedVector;

    for(int i = 0; i < mData.size(); i++){
        returnedVector.push_back(mData[i]);
    }

    return returnedVector;


}






QVariant atlas::gui::CustomEntityModel::data(const QModelIndex &index, int role) const
{

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};


    const auto& entity = mData.at(index.row());

    switch (role) {

    case Id:
        return entity.mId;

    case Latitude:
        return entity.mCoordinate.latitude();
    case Longitude:
        return entity.mCoordinate.longitude();
    case Icon:
        if(entity.mIsHighlited == true){
                return entity.highlitedIcon;
        }
        else
            return entity.mIcon;
    case Heading:
        return entity.mHeading;
    case Speed:
        return entity.mSpeed;
    case Type:
        return (int)entity.mType;
        break;
    default:
        break;
    }
}

QHash<int, QByteArray> atlas::gui::CustomEntityModel::roleNames() const
{
    return mRoleNames;
}

bool atlas::gui::CustomEntityModel::entityExist(int mId)
{
    auto isExist = [mId](const Entity& entity){return entity.mId == mId;};

    return  std::find_if(mData.begin(),mData.end(),isExist) != mData.end();
}




bool atlas::gui::CustomEntityModel::setHighlight(int mId, bool status)
{
    auto returned = [mId](const Entity& entity){return entity.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {IsHighlited};
        beginResetModel();


        it->mIsHighlited = status;

        //emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);
        endResetModel();

        return true;
    }
}

bool atlas::gui::CustomEntityModel::isHighlighted(int mId)
{

    //qDebug() << mData[0].mIsHighlited;
    auto returned = [mId](const Entity& entity){return entity.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        return it->mIsHighlited;
    }
}

QGeoCoordinate atlas::gui::CustomEntityModel::getPos(int mId)
{
    qDebug() << mId;
    auto returned = [mId](const Entity& entity){return entity.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        qDebug() << "bu fie girdi";
        return it->mCoordinate;
    }
}

QGeoCoordinate atlas::gui::CustomEntityModel::midPoint()
{
    QGeoCoordinate a(0,0);
    int k = 0;
    for (int i = 0; i < mData.size(); ++i) {
        if(mData[i].mIsHighlited){

            a.setLatitude(a.latitude() + mData[i].mCoordinate.latitude());
            a.setLongitude(a.longitude() + mData[i].mCoordinate.longitude());
            k++;
        }
    }
    if(k!=0){
        a.setLongitude(a.longitude()/k);
        a.setLatitude(a.latitude()/k);
    }
    return a;
}
