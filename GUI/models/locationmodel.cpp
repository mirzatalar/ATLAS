#include "locationmodel.h"
#include "qdebug.h"

atlas::gui::LocationModel::LocationModel::LocationModel(QObject *parent)
     : QAbstractListModel{parent}
{
    mRoleNames[Id] = "Id" ;
    mRoleNames[Latitude] = "latitude";
    mRoleNames[Longitude] = "longitude";
    mRoleNames[IsHighlited] = "ishighlited";
    mRoleNames[Icon] = "icon";
    mRoleNames[Name] = "name";
}

void atlas::gui::LocationModel::add(int mId, const QGeoCoordinate &mcoordinate,QString name)
{
    beginResetModel();



    Location newLoc(mId, mcoordinate,name);



    newLoc.icon = "qrc:/icons/loc.png";
    newLoc.highLitedcon = "qrc:/icons/loch.png";
    newLoc.mIsHighlited = false;
    mData.push_back(newLoc);



    endResetModel();

}

void atlas::gui::LocationModel::del(int mId)
{

    auto isremoved = [mId](const Location& entity){return entity.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),isremoved);

    beginResetModel();

    mData.erase(itr,itr+1);
    endResetModel();

}

















int  atlas::gui::LocationModel::rowCount(const QModelIndex &parent) const
{
    return mData.size();
}


QVariant atlas::gui::LocationModel::data(const QModelIndex &index, int role) const
{

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};


    const auto& Location = mData.at(index.row());

    switch (role) {

    case Id:
        return Location.mId;
    case Name:
        return Location.name;

    case Latitude:
        return Location.mCoordinate.latitude();
    case Longitude:
        return Location.mCoordinate.longitude();
    case Icon:
        if(Location.mIsHighlited == true){
            return Location.highLitedcon;
        }
        else
            return Location.icon;
    default:
        break;
    }
}

QHash<int, QByteArray> atlas::gui::LocationModel::roleNames() const
{
    return mRoleNames;
}
