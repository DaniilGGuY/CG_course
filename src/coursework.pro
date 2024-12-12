QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3d/zbuffer.cpp \
    main.cpp \
    mainwindow.cpp \
    objects/basemodel.cpp \
    objects/camera.cpp \
    objects/carcasmodel.cpp \
    objects/composite.cpp \
    objects/edge.cpp \
    objects/face.cpp \
    objects/invisibleobject.cpp \
    objects/object.cpp \
    objects/point.cpp \
    objects/strategy/basecentralstrategy.cpp \
    objects/structures/listsurfacestructure.cpp \
    objects/structures/surfacestructure.cpp \
    objects/surfacemodel.cpp \
    objects/visibleobject.cpp \
    plasma/approcplasma.cpp \
    plasma/randomplasma.cpp \
    plasma/baseplasma.cpp \
    plasma/strategy/leastsquares.cpp \
    plasma/strategy/newton.cpp \
    plasma/strategy/spline.cpp \
    transform/cameraaction.cpp \
    transform/rotateaction.cpp \
    transform/scaleaction.cpp \
    transform/transferaction.cpp \
    transform/transformaction.cpp \

HEADERS += \
    3d/zbuffer.h \
    mainwindow.h \
    objects/basemodel.h \
    objects/camera.h \
    objects/carcasmodel.h \
    objects/composite.h \
    objects/edge.h \
    objects/face.h \
    objects/invisibleobject.h \
    objects/object.h \
    objects/point.h \
    objects/strategy/basecentralstrategy.h \
    objects/structures/listsurfacestructure.h \
    objects/structures/surfacestructure.h \
    objects/surfacemodel.h \
    objects/visibleobject.h \
    plasma/approcplasma.h \
    plasma/randomplasma.h \
    plasma/baseplasma.h \
    plasma/strategy/leastsquares.h \
    plasma/strategy/newton.h \
    plasma/strategy/spline.h \
    square_matrix/squarematrix.h \
    square_matrix/squarematrix.hpp \
    transform/cameraaction.h \
    transform/rotateaction.h \
    transform/scaleaction.h \
    transform/transferaction.h \
    transform/transformaction.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
