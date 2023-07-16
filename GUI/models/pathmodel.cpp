#include "pathmodel.h"
#include <iostream>

#include <QDebug>


atlas::gui::PathModel::PathModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames[Id] = "Id" ;
    mRoleNames[Pth] = "pth" ;
    mRoleNames[Color] = "clr";
    mRoleNames[IsHighlited] = "ishighlited";
    mRoleNames[IsVisible] = "isvisible";
    mRoleNames[Opacity] = "oppacity";
}

bool atlas::gui::PathModel::draw(int mId,const QList<QGeoCoordinate>& points,const QString& mColor)
{

    beginInsertRows(QModelIndex(), 0, 0);

    Path newPath(mId,points,mColor);
    newPath.mIsVisible = 1;
    newPath.mIsHighlited = 0;
    newPath.mOpacity = 1;

    mData.push_back(newPath);
    qDebug()<<"Model path: "<<mColor;

    std::cout << "Path " << newPath.mId << " has been added" << std::endl;

    endInsertRows();

    return true;
}

bool atlas::gui::PathModel::move(int mId, const QGeoCoordinate& mCenter){
    auto returned = [mId](const Path& path){return path.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        QVector<int> roles = {Pth};


        double a = it->mPoints.at( it->mPoints.size()/2).latitude();

        double b = it->mPoints.at( it->mPoints.size()/2).longitude();

        double changeinx = mCenter.latitude() - a;
        double changeiny = mCenter.longitude() - b;

        for (int i = 0; i < it->mPoints.size(); ++i) {
            it->mPoints[i].setLatitude(it->mPoints.at(i).latitude() + changeinx);
        }

        for (int i = 0; i < it->mPoints.size(); ++i) {
            it->mPoints[i].setLongitude(it->mPoints.at(i).longitude() + changeiny);
        }


        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }

    return false;
}

bool atlas::gui::PathModel::addPoint(int mId, const QGeoCoordinate& mNewPoint){
    auto returned = [mId](const Path& path){return path.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        QVector<int> roles = {Pth};
        beginResetModel();


        it->mPoints.push_back(mNewPoint);


        //emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);
        endResetModel();
        return true;
    }

    return false;
}

bool atlas::gui::PathModel::removePoint(int mId, const QGeoCoordinate& mDeletedPoint){
    auto returned = [mId](const Path& path){return path.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){
        QVector<int> roles = {Pth};

        for (int i = 0; i < it->mPoints.size(); ++i) {
            if(mDeletedPoint == it->mPoints[i]){
                it->mPoints.removeAt(i);
                break;
            }
        }

        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }

    return false;
}


bool atlas::gui::PathModel::remove(int mId)
{
    qDebug() << "path silindi";
    auto isremoved = [mId](const Path& path){return path.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),isremoved);

    beginResetModel();

    mData.erase(itr,mData.end());
    endResetModel();
    return true;//sor
}

bool  atlas::gui::PathModel::setHighlight(int mId, bool status){

    auto returned = [mId](const Path& path){return path.mId == mId;};

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

bool atlas::gui::PathModel::setColor(int mId, const QString& mColor){
    auto returned = [mId](const Path& path){return path.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {Color};
        it->mColor = mColor;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}

bool atlas::gui::PathModel::setOpacity(int mId, double opacity){
    auto returned = [mId](const Path& path){return path.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {Opacity};
        it->mOpacity = opacity;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}


bool atlas::gui::PathModel::setVisibility(int mId, bool status){
    auto returned = [mId](const Path& path){return path.mId == mId;};

    auto it = std::find_if(mData.begin(),mData.end(),returned);

    if(it != mData.end()){

        QVector<int> roles = {IsVisible};
        it->mIsVisible = status;
        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;
    }
}

bool atlas::gui::PathModel::isExist(int mId)
{
    auto isExist = [mId](const Path& path){return path.mId == mId;};

    return  std::find_if(mData.begin(),mData.end(),isExist) != mData.end();
}

















int  atlas::gui::PathModel::rowCount(const QModelIndex &parent) const
{
    return mData.size();
}


QVariant atlas::gui::PathModel::data(const QModelIndex &index, int role) const
{

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};


    const auto& path = mData.at(index.row());

    switch (role) {

    case Id:
        return path.mId;
    case Color:

        if( path.mIsHighlited == 1){
            return "green";
        }
        return path.mColor;
    case IsHighlited:
        return path.mIsHighlited;
    case Opacity:

        if( path.mIsVisible == 0){
            return 0;
        }
        return path.mOpacity;

    case Pth:
        return QVariant::fromValue(path.mPoints);;

    default:
        break;
    }
}

QHash<int, QByteArray> atlas::gui::PathModel::roleNames() const
{
    return mRoleNames;
}
