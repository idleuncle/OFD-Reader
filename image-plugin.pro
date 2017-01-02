include(OFD-Reader.pri)

TARGET = ofdreader_image
TEMPLATE = lib
CONFIG += plugin
CONFIG += console
static_image_plugin:CONFIG += staticlib

TARGET_SHORT = ofdreaderimg
!isEmpty(PLUGIN_DESTDIR): DESTDIR = $$PLUGIN_DESTDIR

OBJECTS_DIR = objects-image
MOC_DIR = moc-image

INCLUDEPATH += ./app/include
INCLUDEPATH += ./app/plugin

HEADERS = app/plugin/model.h app/plugin/image-plugin/imagemodel.h
SOURCES = app/plugin/image-plugin/imagemodel.cpp

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

static_image_plugin {
    target.path = $${PLUGIN_INSTALL_PATH}
    INSTALLS += target
}
