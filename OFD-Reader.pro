#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T02:26:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OFD-Reader
TEMPLATE = app



INCLUDEPATH += `pkg-config --cflags cairo`
LIBS += `pkg-config --libs cairo`
SOURCES += main.cpp\
    ofdmainwindow.cpp \
    ofdview.cpp \


HEADERS  += \
    typedef.h \
    ofdmainwindow.h \
    ofdview.h \


FORMS    +=


RESOURCES = $${PWD}/ofdviewer.qrc
