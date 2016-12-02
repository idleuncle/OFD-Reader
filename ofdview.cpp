#include "ofdview.h"
#include <QApplication>
#include <QStyle>
#include <QMessageBox>
#include <cairo/cairo.h>
#include <QGraphicsPixmapItem>

OfdView::OfdView(QWidget *parent /*= 0*/)
{
    const QColor backgroundColor = QApplication::style()->standardPalette().color(QPalette::Normal, QPalette::Dark);
    m_pageScene = new QGraphicsScene(this);
    m_pageScene->setBackgroundBrush(backgroundColor); // use window color for the background behind the pages

    this->setScene(m_pageScene);
    this->setMouseTracking(true);

    this->test_cairo();


}

void OfdView::test_cairo()
{
    int iW = 300;

    int iH = 300;
    QImage image(iW, iH, QImage::Format_ARGB32);

    unsigned char* pData =image.bits();

    int iLineStride = image.bytesPerLine();

    cairo_surface_t * pCairoSurface = cairo_image_surface_create_for_data(pData,CAIRO_FORMAT_ARGB32,iW,iH, iLineStride);

    cairo_t* pCairoContext = cairo_create(pCairoSurface);

    cairo_surface_destroy(pCairoSurface);
    if(pCairoSurface)
    {
        cairo_set_source_rgb (pCairoContext, 0.627, 0, 0);
        cairo_select_font_face (pCairoContext, "Simsun",
                                CAIRO_FONT_SLANT_NORMAL,
                                CAIRO_FONT_WEIGHT_NORMAL);

        cairo_set_source_rgb(pCairoContext, 0.5, 0.4, 0.3);
        cairo_set_font_size (pCairoContext, 24.0);
        cairo_move_to (pCairoContext, 10.0, 34.0);

        std::string ss="hello world";
        cairo_show_text (pCairoContext, ss.c_str());
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        m_pageScene->addItem(item);
        cairo_destroy (pCairoContext);
    }




}

OfdView::~OfdView()
{

}

