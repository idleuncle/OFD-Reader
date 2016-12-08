#ifndef LIBOFDENGINE_H
#define LIBOFDENGINE_H
#include <QString>
#include <QList>
#include <cairo/cairo.h>

class libOfdEngine
{
public:
    libOfdEngine();

    bool load(const QString &filename);

    void loadtest();
    cairo_surface_t* test_page1();
    cairo_surface_t* test_page2();
    cairo_surface_t* test_page3();
    QList<cairo_surface_t*> m_pages;
};

#endif // LIBOFDENGINE_H
