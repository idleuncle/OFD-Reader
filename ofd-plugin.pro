TEMPLATE = subdirs

include(OFD-Reader.pri)

TARGET = ofdreader_ofd
TEMPLATE = lib
CONFIG += plugin
static_ofd_plugin:CONFIG += static

#INCLUDEPATH += /Users/charles/workspace/qaa/libofd/tests/firsttest
#INCLUDEPATH += /usr/local/include/ofd/include
#INCLUDEPATH += /usr/local/include/ofd
INCLUDEPATH += /Users/charles/workspace/yr_prj/gitlab/libofd/libofd-0.7/include
INCLUDEPATH += /Users/charles/workspace/yr_prj/gitlab/libofd/libofd-0.7
INCLUDEPATH += ./sources

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lcairo
#LIBS += -L/usr/local/include/ofd/build/lib -lofd
LIBS += -L/Users/charles/workspace/yr_prj/gitlab/libofd/libofd-0.7/build/lib -lofd -lutils


QT += core xml gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ./app/include
INCLUDEPATH += ./app/plugin

HEADERS = app/plugin/model.h app/plugin/ofd-plugin/ofdmodel.h
SOURCES = app/plugin/ofd-plugin/ofdmodel.cpp

