#include "pathmodel.h"

PathModel::PathModel(QObject *parent):
    QAbstractListModel(parent)
{

    connect(this, &QAbstractListModel::dataChanged, this, &PathModel::pathChanged);

}
 void PathModel::addPosition(const QGeoCoordinate &coordinate) {

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mData.append(QVariant::fromValue(coordinate));
    emit pathChanged();
    endInsertRows();


}

 void PathModel::drawPath(int mId, std::vector <QGeoCoordinate> &points){

    for (int var = 0; var < points.size(); ++var) {
        addPosition(points[var]);
    }




 }

int PathModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mData.count();
}

QVariant PathModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mData.count())
    {
        return QVariant();
    }
    if (role == positionRole)
    {
        return QVariant::fromValue(mData[index.row()]);
    }
    return QVariant();
}

QHash<int, QByteArray> PathModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[positionRole] = "position";
    return roles;
}


QVariantList PathModel::path() const
{
    return mData;
}
