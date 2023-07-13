#ifndef CIRCLEMODEL_H
#define CIRCLEMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QGeoCoordinate>
#include "Circle.h"

namespace atlas::gui {
class CircleModel : public QAbstractListModel
{
public:

    CircleModel(QObject *parent = nullptr);
    enum CirclesRole
    {
        Id  = 0,
        Latitude ,
        Longitude,
        Color,
        Opacity,
        IsVisible,
        IsHighlited,
        Radius

    };

    bool draw(int mId, const QGeoCoordinate& mCenter,const QGeoCoordinate &mCircumCoor, const QString& mColor);
    bool move(int mId, const QGeoCoordinate& mPos);
    bool setCircumf(int mId, const QGeoCoordinate& mCircumCoor);
    bool remove(int mId);
    bool setHighlight(int mId, bool status);
    bool setOpacity(int mId, double opacity);
    bool setVisibility(int mId, bool status);
    bool setColor(int mId,const QString& mColor);
    bool isExist(int mId);

    // QAbstracListModelInterface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    std::vector<Circle> mData;
    QHash<int, QByteArray> mRoleNames;

};
}
#endif // CIRCLEMODEL_H





