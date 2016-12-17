#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T08:57:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OFD-Reader
TEMPLATE = app
CONFIG += static

DEFINES += PLUGIN_INSTALL_PATH=\\\"$${PLUGIN_INSTALL_PATH}\\\"

!without_image {
    DEFINES += WITH_IMAGE

    static_image_plugin {
        isEmpty(IMAGE_PLUGIN_NAME):IMAGE_PLUGIN_NAME = libofdreader_image.a

        DEFINES += STATIC_IMAGE_PLUGIN
        LIBS += $$IMAGE_PLUGIN_NAME
        PRE_TARGETDEPS += $$IMAGE_PLUGIN_NAME
    }
    else {
        isEmpty(IMAGE_PLUGIN_NAME):IMAGE_PLUGIN_NAME = libofdreader_image.dylib
    }

    DEFINES += IMAGE_PLUGIN_NAME=\\\"$${IMAGE_PLUGIN_NAME}\\\"
}



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

