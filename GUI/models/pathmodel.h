
#ifndef PATHMODEL_H
#define PATHMODEL_H

#include <QAbstractListModel>
#include <QTimer>
#include <QGeoCoordinate>
#include <QGeoPath>
#include <QVariantList>


class PathModel :  public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList path READ path NOTIFY pathChanged)

public:
    enum MarkerRoles {
        positionRole = Qt::UserRole + 1
    };

    PathModel(QObject *parent = nullptr);


    void drawPath(int mId, std::vector <QGeoCoordinate> &points);
    void addPosition(const QGeoCoordinate &coordinate);
    int rowCount(const QModelIndex &parent = QModelIndex() ) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const  ;
    QVariantList path() const;


private:
    QHash<int, QByteArray> roleNames() const ;
    QVariantList mData;;

signals:
    void pathChanged();

};
#endif // PATHMODEL_H


