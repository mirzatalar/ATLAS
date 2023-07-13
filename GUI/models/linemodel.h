#ifndef LINEMODEL_H
#define LINEMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QGeoCoordinate>
#include "line.h"

namespace atlas::gui {
    class LineModel : public QAbstractListModel
    {
    public:

        LineModel(QObject *parent = nullptr);
        enum LinesRole
        {
            Id  = 0,
            Latitude1 ,
            Longitude1,
            Latitude2 ,
            Longitude2,
            Color,
            IsVisible,
            Opacity,
            IsHighlited

        };

        bool draw(int mId, const QGeoCoordinate& mcoordinate1,const QGeoCoordinate& mcoordinate2,const QString& mColor);
        bool move(int mId, const QGeoCoordinate& mCenter);
        bool remove(int mId);
        bool setHighlight(int mId, bool status);
        bool setOpacity(int mId, double opacity);
        bool setVisibility(int mId, bool status);
        bool setColor(int mId, const QString& mColor);
        bool isExist(int mId);

        bool setEndLine(int mId,const QGeoCoordinate &coordinate2);
        bool setBeginLine(int mId,const QGeoCoordinate &coordinate1);

        // QAbstracListModelInterface
        int rowCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QHash<int, QByteArray> roleNames() const;

    private:
        std::vector<Line> mData;
        QHash<int, QByteArray> mRoleNames;

    };
}
#endif // LINEMODEL_H





