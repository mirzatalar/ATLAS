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
            IsHighlited

        };

        bool drawLine(int mId, const QGeoCoordinate& mcoordinate1,const QGeoCoordinate& mcoordinate2,const QString& mColor, bool mIsVisible, bool mIsHighlited);
        bool removeLine(int mId);

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





