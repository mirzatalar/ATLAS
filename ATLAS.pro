QT += quick location positioning widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/actioncontroller.cpp \
    Controller/entitycontroller.cpp \
    Controller/maincontroller.cpp \
    Controller/mapcontroller.cpp \
    Controller/mapdrawer.cpp \
    Controller/mapmouseactioncontroller.cpp \
    GUI/models/Line.cpp \
    GUI/models/circle.cpp \
    GUI/models/circlemodel.cpp \
    GUI/models/customentitymodel.cpp \
    GUI/models/entity.cpp \
    GUI/models/gridmodel.cpp \
    GUI/models/linemodel.cpp \
    GUI/models/path.cpp \
    GUI/models/pathmodel.cpp \
    GUI/models/rectangle.cpp \
    GUI/models/rectanglemodel.cpp \
    main.cpp

HEADERS += \
    Controller/actioncontroller.h \
    Controller/entitycontroller.h \
    Controller/maincontroller.h \
    Controller/mapcontroller.h \
    Controller/mapdrawer.h \
    Controller/mapmouseactioncontroller.h \
    GUI/models/EntityType.h \
    GUI/models/circle.h \
    GUI/models/circlemodel.h \
    GUI/models/customentitymodel.h \
    GUI/models/entity.h \
    GUI/models/gridmodel.h \
    GUI/models/line.h \
    GUI/models/linemodel.h \
    GUI/models/path.h \
    GUI/models/pathmodel.h \
    GUI/models/rectangle.h \
    GUI/models/rectanglemodel.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc

DISTFILES +=
