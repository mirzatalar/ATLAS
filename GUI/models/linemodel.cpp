#include "linemodel.h"
#include <iostream>

#include <QDebug>


atlas::gui::LineModel::LineModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames[Id] = "Id" ;
    mRoleNames[Latitude1] = "latitude1";
    mRoleNames[Longitude1] = "longitude1";
    mRoleNames[Latitude2] = "latitude2";
    mRoleNames[Longitude2] = "longitude2";
    mRoleNames[Color] = "clr";
    mRoleNames[IsHighlited] = "ishighlited";
    mRoleNames[IsVisible] = "isvisible";
    mRoleNames[Opacity] = "oppacity";
    mRoleNames[Distance] = "dstnc";
}

bool atlas::gui::LineModel::draw(int mId,const QGeoCoordinate &mcoordinate1, const QGeoCoordinate &mcoordinate2, const QString &mColor)
{

    beginResetModel();


    Line newLine(mId,mcoordinate1, mcoordinate2, mColor);
    newLine.mIsVisible = 1;
    newLine.mIsHighlited = 0;
    newLine.mOpacity = 1;


    mData.push_back(newLine);





    endResetModel();

    return true;
}

bool atlas::gui::LineModel::move(int mId, const QGeoCoordinate& mCenter){
    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        QVector<int> roles = {Latitude1, Longitude1,Latitude2, Longitude2};


        double a = (it->mCoordinate1.latitude() + it->mCoordinate2.latitude())/2;

        double b = (it->mCoordinate1.longitude() + it->mCoordinate2.longitude())/2;

        double changeinx = mCenter.latitude() - a;
        double changeiny = mCenter.longitude() - b;

        QGeoCoordinate new1;
        QGeoCoordinate new2;

        new1.setLatitude(it->mCoordinate1.latitude() + changeinx);
        new2.setLatitude(it->mCoordinate2.latitude() + changeinx);

        new1.setLongitude(it->mCoordinate1.longitude() + changeiny);
        new2.setLongitude(it->mCoordinate2.longitude() + changeiny);

        beginResetModel();

        it->mCoordinate1 = new1;
        it->mCoordinate2 = new2;


        endResetModel();

        return true;
    }

    return false;
}



bool atlas::gui::LineModel::remove(int mId)
{

    auto isremoved = [mId](const Line& line){return line.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),isremoved);

    beginResetModel();

    mData.erase(itr,mData.end());
    endResetModel();
    return true;//sor
}

bool  atlas::gui::LineModel::setHighlight(int mId, bool status){

    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        beginResetModel();
        QVector<int> roles = {IsHighlited};
        it->mIsHighlited = status;
        endResetModel();

        return true;
    }
}

bool atlas::gui::LineModel::setColor(int mId, const QString& mColor){
    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);


        QVector<int> roles = {Color};
        it->mColor = mColor;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;

}

bool atlas::gui::LineModel::setOpacity(int mId, double opacity){
        for (int var = 0; var < mData.size(); ++var) {
        if(mData[var].mId == mId){
            beginResetModel();

            QVector<int> roles = {Opacity};
            mData[var].mOpacity = opacity;
            endResetModel();
        }
        }



        return true;
    }



bool atlas::gui::LineModel::setVisibility(int mId, bool status){
    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {IsVisible};
        it->mIsVisible = status;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}

bool atlas::gui::LineModel::isExist(int mId)
{
    auto isExist = [mId](const Line& line){return line.mId == mId;};

    return  std::find_if(mData.begin(),mData.end(),isExist) != mData.end();
}

bool atlas::gui::LineModel::isHighlighted(int mId)
{
    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        return it->mIsHighlited;
    }
}




bool atlas::gui::LineModel::setEndLine(int mId,const QGeoCoordinate &coordinate2){

    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {Latitude2, Longitude2,Distance};
        it->distance = it->mCoordinate1.distanceTo(coordinate2);

        it->mCoordinate2 = coordinate2;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);
        //qDebug() << "end line updated :: "<< coordinate2;
        return true;
    }


}




bool atlas::gui::LineModel::setBeginLine(int mId,const QGeoCoordinate &coordinate2){

    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {Latitude1, Longitude1};
        it->mCoordinate1 = coordinate2;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);
        //qDebug() << "end line updated :: "<< coordinate2;
        return true;
    }


}











int  atlas::gui::LineModel::rowCount(const QModelIndex &parent) const
{
    return mData.size();
}


QVariant atlas::gui::LineModel::data(const QModelIndex &index, int role) const
{

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};


    const auto& line = mData.at(index.row());

    switch (role) {

    case Id:
        return line.mId;

    case Latitude1:
        return line.mCoordinate1.latitude();
    case Longitude1:
        return line.mCoordinate1.longitude();
    case Latitude2:
        return line.mCoordinate2.latitude();
    case Longitude2:
        return line.mCoordinate2.longitude();
    case Distance:
        return line.distance;
    case Color:

        if( line.mIsHighlited == 1){
            return "green";
        }
        return line.mColor;
    case IsHighlited:
        return line.mIsHighlited;
    case Opacity:

        if( line.mIsVisible == 0){
            return 0;
        }
        return line.mOpacity;
    default:
        break;
    }
}

QHash<int, QByteArray> atlas::gui::LineModel::roleNames() const
{
    return mRoleNames;
}
