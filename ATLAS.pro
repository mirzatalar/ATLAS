QT += quick location positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/maincontroller.cpp \
    Controller/mapcontroller.cpp \
    Controller/mapdrawer.cpp \
    GUI/models/Line.cpp \
    GUI/models/circle.cpp \
    GUI/models/circlemodel.cpp \
    GUI/models/linemodel.cpp \
    GUI/models/path.cpp \
    GUI/models/pathmodel.cpp \
    main.cpp

HEADERS += \
    Controller/maincontroller.h \
    Controller/mapcontroller.h \
    Controller/mapdrawer.h \
    GUI/models/circle.h \
    GUI/models/circlemodel.h \
    GUI/models/line.h \
    GUI/models/linemodel.h \
    GUI/models/path.h \
    GUI/models/pathmodel.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc

DISTFILES +=
