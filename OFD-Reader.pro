TEMPLATE = subdirs

SUBDIRS += \
    app


!without_image {
    SUBDIRS += image-plugin.pro
    app.pro.depends = image-plugin.pro
}


!without_ofd {
    SUBDIRS += ofd-plugin.pro
    app.pro.depends = ofd-plugin.pro
}
