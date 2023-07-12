#ifndef PATHMODEL_H
#define PATHMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QGeoCoordinate>
#include "path.h"

namespace atlas::gui {
class PathModel : public QAbstractListModel
{
public:

    PathModel(QObject *parent = nullptr);
    enum PathRoles
    {
        Id  = 0,
        Color,
        IsVisible,
        Opacity,
        IsHighlited,
        Pth

    };

    bool draw(int mId,const QList<QGeoCoordinate>& points,const QString& mColor);
    bool move(int mId, const QGeoCoordinate& mCenter);
    bool remove(int mId);
    bool addPoint(int mId,const QGeoCoordinate& mNewPoint);
    bool removePoint(int mId,const QGeoCoordinate& mDeletedPoint);
    bool setHighlight(int mId, bool status);
    bool setOpacity(int mId, double opacity);
    bool setVisibility(int mId, bool status);
    bool setColor(int mId, const QString& mColor);
    bool isExist(int mId);

    // QAbstracListModelInterface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    std::vector<Path> mData;
    QHash<int, QByteArray> mRoleNames;

};
}
#endif // PATHMODEL_H





