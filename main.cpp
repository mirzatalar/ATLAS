#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QRandomGenerator>
#include <Controller/maincontroller.h>
#include <iostream>
#include "Controller/mapdrawer.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    //Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)

    QQmlApplicationEngine engine;

    atlas::controller::MainController mainController;



    mainController.init(&engine);



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);






    return app.exec();
}
