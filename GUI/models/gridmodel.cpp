#include "gridmodel.h"
#include <QDebug>

atlas::gui::GridModel::GridModel(QObject *parent)
    : QAbstractListModel{parent}
{
    mRoleNames[Latitude1] = "latitude1";
    mRoleNames[Longitude1] = "longitude1";
    mRoleNames[Latitude2] = "latitude2";
    mRoleNames[Longitude2] = "longitude2";
}

bool atlas::gui::GridModel::draw(const QGeoRectangle &rec)
{



    double a = rec.topLeft().longitude(); // 22
    double b = rec.topRight().longitude(); // 48
    double c = rec.bottomRight().latitude(); // 34
    double d = rec.topRight().latitude(); //45

    double ennumber = abs(rec.bottomLeft().latitude() - rec.topLeft().latitude()) ;
    double boynumber =abs(rec.bottomLeft().longitude() - rec.topRight().longitude()) ;


    mData.clear();
    beginResetModel();

    for (int i = 1; i <= ennumber; ++i) {
        //mMapDrawer->drawLine(500,QGeoCoordinate(c + i*(d-c)/ennumber,a), QGeoCoordinate(c + i*(d-c)/ennumber,b+1),"white");
        Line newLine(500,QGeoCoordinate(c + i*(d-c)/ennumber,a), QGeoCoordinate(c + i*(d-c)/ennumber,b+1), "white");
        mData.push_back(newLine);


    }

    for (int i = 1; i <= boynumber; ++i) {
        //mMapDrawer->drawLine(500,QGeoCoordinate(c-1,a + i*(b-a)/boynumber), QGeoCoordinate(d+1,a + i*(b-a)/boynumber),"white");
         Line newLine(500,QGeoCoordinate(c-1,a + i*(b-a)/boynumber), QGeoCoordinate(d+1,a + i*(b-a)/boynumber), "white");
        mData.push_back(newLine);
    }

       endResetModel();
    return true;
}

void atlas::gui::GridModel::clear()
{
    beginResetModel();
       mData.clear();
    endResetModel();
}




int  atlas::gui::GridModel::rowCount(const QModelIndex &parent) const
{
    return mData.size();
}


QVariant atlas::gui::GridModel::data(const QModelIndex &index, int role) const
{

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};


    const auto& line = mData.at(index.row());

    switch (role) {


    case Latitude1:
        return line.mCoordinate1.latitude();
    case Longitude1:
        return line.mCoordinate1.longitude();
    case Latitude2:
        return line.mCoordinate2.latitude();
    case Longitude2:
        return line.mCoordinate2.longitude();

    default:
        break;
    }
}

QHash<int, QByteArray> atlas::gui::GridModel::roleNames() const
{
    return mRoleNames;
}
