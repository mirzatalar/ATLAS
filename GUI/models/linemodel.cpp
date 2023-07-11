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
}

bool atlas::gui::LineModel::drawLine(int mId,const QGeoCoordinate &mcoordinate1, const QGeoCoordinate &mcoordinate2, const QString &mColor, bool mIsVisible, bool mIsHighlited)
{

    beginInsertRows(QModelIndex(), 0, 0);

    Line newLine(mId,mcoordinate1, mcoordinate2, mColor,mIsVisible, mIsHighlited);

    mData.push_back(newLine);

    qDebug()<<"Model: "<<mColor;

    std::cout << "Line " << newLine.mId << " has been added" << std::endl;

    endInsertRows();

    return true;
}





bool atlas::gui::LineModel::removeLine(int mId)
{
    auto isremoved = [mId](const Line& line){return line.mId == mId;};

    auto itr = std::find_if(mData.begin(),mData.end(),isremoved);

    beginRemoveRows(QModelIndex(), std::distance(mData.begin(), itr), std::distance(itr, mData.end()));
    mData.erase(itr,mData.end());
    endRemoveRows();


    return itr != mData.end();
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
        return line.mColor;
    case IsHighlited:
        return line.mIsHighlited;
    case IsVisible:
        return line.mIsVisible;
    default:
        break;
    }
}

QHash<int, QByteArray> atlas::gui::LineModel::roleNames() const
{
    return mRoleNames;
}
