#include "GUI/models/circlemodel.h"
#include <iostream>

#include <QDebug>


atlas::gui::CircleModel::CircleModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames[Id] = "Id" ;
    mRoleNames[Latitude] = "latitude";
    mRoleNames[Longitude] = "longitude";
    mRoleNames[Color] = "clr";
    mRoleNames[IsHighlited] = "ishighlited";
    mRoleNames[IsVisible] = "isvisible";
    mRoleNames[Opacity] = "oppacity";
    mRoleNames[Radius] = "rds";
    mRoleNames[Area] = "circleArea";
}

bool atlas::gui::CircleModel::draw(int mId,const QGeoCoordinate &mCenter, const QGeoCoordinate &mCircumCoor, const QString &mColor)
{

    beginResetModel();//todo



    Circle newCircle(mId,mCenter,mCircumCoor, mColor);
    newCircle.mIsVisible = 1;
    newCircle.mIsHighlited = 0;
    newCircle.mOpacity = 0.5;
    newCircle.radius = mCenter.distanceTo(mCircumCoor);

    mData.push_back(newCircle);


    qDebug()<<"Model: "<<mColor;

    std::cout << "Circle " << newCircle.mId << " has been added" << std::endl;


    endResetModel();




    return true;
}




bool atlas::gui::CircleModel::move(int mId, const QGeoCoordinate &newCoordinate)
{
    auto returned = [mId](const Circle& circle){return circle.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        QVector<int> roles = {Latitude, Longitude};

        beginResetModel();

        it->mCenter.setLatitude(it->mCenter.latitude() + newCoordinate.latitude());
        it->mCenter.setLongitude(it->mCenter.longitude() + newCoordinate.longitude());

        endResetModel();



        return true;
    }

    return false;
}

bool atlas::gui::CircleModel::setCircumf(int mId, const QGeoCoordinate &newCoordinate)
{
    auto returned = [mId](const Circle& circle){return circle.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        QVector<int> roles = {Radius,Area};

        it->radius = it->mCenter.distanceTo(newCoordinate);
        it->area = (3.141592)*( it->radius)*( it->radius);

        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }

    return false;
}

bool atlas::gui::CircleModel::remove(int mId)
{

    auto isremoved = [mId](const Circle& Circle){return Circle.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),isremoved);

    beginResetModel();

    mData.erase(itr,mData.end());
    endResetModel();



    return true;//sor
}

bool  atlas::gui::CircleModel::setHighlight(int mId, bool status){

    auto returned = [mId](const Circle& Circle){return Circle.mId == mId;};

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


bool atlas::gui::CircleModel::setOpacity(int mId, double opacity){
    auto returned = [mId](const Circle& Circle){return Circle.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {Opacity};
        it->mOpacity = opacity;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}


bool atlas::gui::CircleModel::setVisibility(int mId, bool status){
    auto returned = [mId](const Circle& Circle){return Circle.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {IsVisible};
        it->mIsVisible = status;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}

bool atlas::gui::CircleModel::setColor(int mId,const QString& mColor) {
    auto returned = [mId](const Circle& Circle){return Circle.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {Color};
        it->mColor = mColor;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}




bool atlas::gui::CircleModel::isExist(int mId)
{
    auto isExist = [mId](const Circle& circle){return circle.mId == mId;};

    return  std::find_if(mData.begin(),mData.end(),isExist) != mData.end();
}




bool atlas::gui::CircleModel::isHighlighted(int mId)
{
    auto returned = [mId](const Circle& Circle){return Circle.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        return it->mIsHighlited;
    }
}


bool atlas::gui::CircleModel::isInCoor( int mId, const QGeoCoordinate& m1,const QGeoCoordinate &m2){


    auto returned = [mId](const Circle& Circle){return Circle.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        if(it->mCenter.latitude() <= m1.latitude() && it->mCenter.latitude() >= m2.latitude() && it->mCenter.longitude() >= m1.longitude() && it->mCenter.longitude() <= m2.longitude()){

            return true;
        }
        else{

            return false;
        }
    }



}

QGeoCoordinate atlas::gui::CircleModel::midPoint()
{
    QGeoCoordinate a(0,0);
    int k = 0;
    for (int i = 0; i < mData.size(); ++i) {
        if(mData[i].mIsHighlited){

        a.setLatitude(a.latitude() + mData[i].mCenter.latitude());
        a.setLongitude(a.longitude() + mData[i].mCenter.longitude());
        k++;
        }
    }
    if(k!=0){
        a.setLongitude(a.longitude()/k);
        a.setLatitude(a.latitude()/k);
    }
    return a;
}



int  atlas::gui::CircleModel::rowCount(const QModelIndex &parent) const
{
    return mData.size();
}


QVariant atlas::gui::CircleModel::data(const QModelIndex &index, int role) const
{

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};


    const auto& Circle = mData.at(index.row());

    switch (role) {

    case Id:
        return Circle.mId;

    case Latitude:
        return Circle.mCenter.latitude();
    case Longitude:
        return Circle.mCenter.longitude();
    case Radius:
        return Circle.radius;
    case Area:
        return Circle.area;
    case Color:

        if( Circle.mIsHighlited == 1){
            return "green";
        }
        return Circle.mColor;
    case IsHighlited:
        return Circle.mIsHighlited;
    case Opacity:

        if( Circle.mIsVisible == 0){
            return 0;
        }
        return Circle.mOpacity;
    default:
        break;
    }
}

QHash<int, QByteArray> atlas::gui::CircleModel::roleNames() const
{
    return mRoleNames;
}
