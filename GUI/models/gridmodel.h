#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include <QGeoRectangle>
#include "line.h"

namespace atlas::gui {
class GridModel :public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GridModel(QObject *parent = nullptr);

    enum LinesRole
    {
        Latitude1 ,
        Longitude1,
        Latitude2 ,
        Longitude2,

    };

     bool draw(const QGeoRectangle& rec);
    void clear();

    // QAbstracListModelInterface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    std::vector<Line> mData;
    QHash<int, QByteArray> mRoleNames;




};
}
#endif // GRIDMODEL_H
