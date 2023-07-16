#ifndef RECTANGLEMODEL_H
#define RECTANGLEMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QGeoCoordinate>
#include <GUI/models/rectangle.h>


namespace atlas::gui {
    class RectangleModel : public QAbstractListModel
    {
        Q_OBJECT
    public:
        explicit RectangleModel(QObject *parent = nullptr);
        enum RectangleRoles
        {
            Latitude1 ,
            Longitude1,
            Latitude2 ,
            Longitude2,

        };

        bool draw(const QGeoCoordinate& m1,const QGeoCoordinate &m2);
        bool setEndl(const QGeoCoordinate& m2);
        bool remove();

        // QAbstracListModelInterface
        int rowCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QHash<int, QByteArray> roleNames() const;

    private:
        std::vector<Rectangle> mData;
        QHash<int, QByteArray> mRoleNames;


    };
}
#endif // RECTANGLEMODEL_H
