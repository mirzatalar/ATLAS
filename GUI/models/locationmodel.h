#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QGeoCoordinate>
#include <GUI/models/location.h>
namespace atlas::gui {
class LocationModel : public QAbstractListModel

{
    Q_OBJECT
public:
    explicit LocationModel(QObject *parent = nullptr);
    enum RectangleRoles
    {
        Id,
        Latitude,
        Longitude,
        IsHighlited,
        Icon
    };

    void add(int mId, const QGeoCoordinate& mcoordinate);
    void del(int mId);


    // QAbstracListModelInterface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    std::vector<Location> mData;
    QHash<int, QByteArray> mRoleNames;


};
}
#endif // LOCATIONMODEL_H
