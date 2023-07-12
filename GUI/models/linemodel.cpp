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
}

bool atlas::gui::LineModel::draw(int mId,const QGeoCoordinate &mcoordinate1, const QGeoCoordinate &mcoordinate2, const QString &mColor)
{

    beginInsertRows(QModelIndex(), 0, 0);


    Line newLine(mId,mcoordinate1, mcoordinate2, mColor);
    newLine.mIsVisible = 1;
    newLine.mIsHighlited = 0;
    newLine.mOpacity = 1;

    mData.push_back(newLine);


    qDebug()<<"Model: "<<mColor;

    std::cout << "Line " << newLine.mId << " has been added" << std::endl;

    endInsertRows();

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

        it->mCoordinate1 = new1;
        it->mCoordinate2 = new2;


        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }

    return false;
}



bool atlas::gui::LineModel::remove(int mId)
{

    auto isremoved = [mId](const Line& line){return line.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),isremoved);

    beginRemoveRows(QModelIndex(), std::distance(mData.begin(), itr), std::distance(itr, mData.end()));

    mData.erase(itr,mData.end());
    endRemoveRows();
    return true;//sor
}

bool  atlas::gui::LineModel::setHighlight(int mId, bool status){

    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {IsHighlited};
        it->mIsHighlited = status;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}

bool atlas::gui::LineModel::setColor(int mId, const QString& mColor){
    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {Color};
        it->mColor = mColor;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}

bool atlas::gui::LineModel::setOpacity(int mId, double opacity){
    auto returned = [mId](const Line& line){return line.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {Opacity};
        it->mOpacity = opacity;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
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
