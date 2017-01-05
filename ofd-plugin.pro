TEMPLATE = subdirs

include(OFD-Reader.pri)

TARGET = ofdreader_ofd
TEMPLATE = lib
CONFIG += plugin
static_ofd_plugin:CONFIG += static

#INCLUDEPATH += /Users/charles/workspace/qaa/libofd/tests/firsttest
INCLUDEPATH += /Users/charles/workspace/qaa/libofd/include
INCLUDEPATH += /Users/charles/workspace/qaa/libofd
INCLUDEPATH += /usr/local/include
INCLUDEPATH += ./sources

INCLUDEPATH += /usr/local/Cellar/cairo/1.14.6_1/include
LIBS += -L/usr/local/lib -lcairo
 #    LIBS += /usr/local/Cellar/poppler/0.49.0/lib
LIBS += -L/Users/charles/workspace/qaa/libofd/build/lib -lofd


QT += core xml gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ./app/include
INCLUDEPATH += ./app/plugin

HEADERS = app/plugin/model.h app/plugin/ofd-plugin/ofdmodel.h
SOURCES = app/plugin/ofd-plugin/ofdmodel.cpp

