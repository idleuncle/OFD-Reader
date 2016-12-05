#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T02:26:03
#
#-------------------------------------------------
QT_CONFIG -= no-pkg-config
QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKG_CONFIG = /usr/local/bin/pkg-config
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OFD-Reader
TEMPLATE = app

macx {

    INCLUDEPATH += /usr/local/Cellar/cairo/1.14.6_1/include
    LIBS += -L/usr/local/lib -lcairo
}

unix:!macx {
    INCLUDEPATH += `pkg-config --cflags cairo`
    LIBS += `pkg-config --libs cairo`
}

SOURCES += main.cpp\
    ofdmainwindow.cpp \
    ofdview.cpp \
    libofdengine.cpp


HEADERS  += \
    typedef.h \
    ofdmainwindow.h \
    ofdview.h \
    libofdengine.h


FORMS    +=


RESOURCES = $${PWD}/ofdviewer.qrc
