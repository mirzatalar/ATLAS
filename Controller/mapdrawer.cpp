#include "mapdrawer.h"
#include "qqmlapplicationengine.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <iostream>


atlas::controller::MapDrawer::MapDrawer(QObject *parent, QQmlApplicationEngine *engine)
    : QObject{parent}
{
    qmlRegisterType<atlas::gui::LineModel>("com.bitessavunma.linemodel", 1, 0, "LineModel");
    engine->rootContext()->setContextProperty("lineModel",  &mLineModel);
}


bool atlas::controller::MapDrawer::drawLine(int mId, const QGeoCoordinate &coordinate1,const QGeoCoordinate &coordinate2,const QString& mColor, bool IsVisible, bool IsHighlited)
{

    // Some controlss

    qDebug()<<"Draw Line:: "<<mColor;

    std::cout << IsHighlited << std::endl;

    return mLineModel.drawLine( mId, coordinate1, coordinate2, mColor, IsVisible, IsHighlited);


}

bool atlas::controller::MapDrawer::removeLine(int mId)

{

    // Some Controls..

    return  mLineModel.removeLine(mId);
}
