#include "rectanglemodel.h"

atlas::gui::RectangleModel::RectangleModel(QObject *parent)
        : QAbstractListModel{parent}
{
    mRoleNames[Latitude1] = "latitude1";
    mRoleNames[Longitude1] = "longitude1";
    mRoleNames[Latitude2] = "latitude2";
    mRoleNames[Longitude2] = "longitude2";
}





bool atlas::gui::RectangleModel::draw(const QGeoCoordinate &c1, const QGeoCoordinate &c2)
{

    beginResetModel();//todo



    Rectangle newRectangle(c1,c2);

    mData.push_back(newRectangle);





    endResetModel();




    return true;
}






bool atlas::gui::RectangleModel::setEndl(const QGeoCoordinate &m2)
{

//    beginResetModel();

//    (mData.begin())->coor2 = m2;

//    endResetModel();

//    return true;



    auto it = mData.begin();


        QVector<int> roles = {Latitude2,Longitude2};

        it->coor2 = m2;


        emit dataChanged(index(std::distance(mData.begin(), it), 0), index(std::distance(mData.begin(), it), 0), roles);

        return true;

}


bool atlas::gui::RectangleModel::remove()
{



    beginResetModel();

    mData.erase(mData.begin());
    endResetModel();



    return true;//sor
}














int  atlas::gui::RectangleModel::rowCount(const QModelIndex &parent) const
{
    return mData.size();
}


QVariant atlas::gui::RectangleModel::data(const QModelIndex &index, int role) const
{

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};


    const auto& Rectangle = mData.at(index.row());

    switch (role) {


    case Latitude1:
        return Rectangle.coor1.latitude();
    case Longitude1:
        return Rectangle.coor1.longitude();
    case Latitude2:
        return Rectangle.coor2.latitude();
    case Longitude2:
        return Rectangle.coor2.longitude();

    default:
        break;
    }
}

QHash<int, QByteArray> atlas::gui::RectangleModel::roleNames() const
{
    return mRoleNames;
}
