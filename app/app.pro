#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T08:57:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OFD-Reader
TEMPLATE = app



INCLUDEPATH += ./include
INCLUDEPATH += ./plugin
HEADERS  += \
    include/libofdengine.h \
    include/ofdmainwindow.h \
    include/documentcontroller.h \
    include/pageitem.h \
    include/typedef.h \
    include/documentview.h \
    plugin/model.h \
    include/global.h \
    include/pluginhandler.h

#FORMS    += mainwindow.ui

SOURCES += \
    src/libofdengine.cpp \
    src/main.cpp \
    src/ofdmainwindow.cpp \
    src/documentcontroller.cpp \
    src/pageitem.cpp \
    src/documentview.cpp \
    plugin/model.cpp \
    src/global.cpp \
    src/pluginhandler.cpp


 macx {
 # macx
    QT_CONFIG -= no-pkg-config
     INCLUDEPATH += /usr/local/Cellar/cairo/1.14.6_1/include
#     LIBS += -L/usr/local/lib -lcairo
 }

 unix:!macx {
 # linux only
     INCLUDEPATH += `pkg-config --cflags cairo`
     LIBS += `pkg-config --libs cairo`
 }

 win32 {
 # windows only
 }

RESOURCES = $${PWD}/res/ofdviewer.qrc

