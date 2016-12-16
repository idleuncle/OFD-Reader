TEMPLATE = subdirs

SUBDIRS += \
    app


!without_image {
    SUBDIRS += image-plugin.pro
    app.pro.depends = image-plugin.pro
}
