QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3d/objects/camera/camera.cpp \
    3d/objects/light/light.cpp \
    3d/objects/model/surfacemodel.cpp \
    3d/render/zbuffer.cpp \
    3d/scene3d.cpp \
    main.cpp \
    mainwindow.cpp \
    plasma/approcplasma.cpp \
    plasma/randomplasma.cpp \
    plasma/baseplasma.cpp \
    plasma/strategy/leastsquares.cpp \
    plasma/strategy/newton.cpp \
    plasma/strategy/spline.cpp \

HEADERS += \
    3d/objects/camera/camera.h \
    3d/objects/light/light.h \
    3d/objects/model/surfacemodel.h \
    3d/render/zbuffer.h \
    3d/scene3d.h \
    mainwindow.h \
    plasma/approcplasma.h \
    plasma/randomplasma.h \
    plasma/baseplasma.h \
    plasma/strategy/leastsquares.h \
    plasma/strategy/newton.h \
    plasma/strategy/spline.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
