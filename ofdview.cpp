#include "ofdview.h"
#include "typedef.h"
#include <QApplication>
#include <QStyle>
#include <QMessageBox>
#include <cairo/cairo.h>
#include <QGraphicsPixmapItem>

OfdView::OfdView(libOfdEngine* engine,QWidget *parent /*= 0*/)
{
    const QColor backgroundColor = QApplication::style()->standardPalette().color(QPalette::Normal, QPalette::Dark);
    m_pageScene = new QGraphicsScene(this);
    m_pageScene->setBackgroundBrush(backgroundColor); // 背景色

    this->setScene(m_pageScene);
    this->setMouseTracking(true);
    this->setofdengine(engine);



}

cairo_surface_t* getcairsurface()
{
    cairo_surface_t *surface;
    cairo_t *cr;

    surface =
            cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 2000, 2000);
    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_select_font_face (cr, "Simsun",
                            CAIRO_FONT_SLANT_NORMAL,
                            CAIRO_FONT_WEIGHT_NORMAL);

//    cairo_rectangle (cr, 20, 20,  2000,2000);

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_fill (cr);
    cairo_set_font_size (cr, 24.0);
    cairo_move_to (cr, 10.0, 34.0);

    std::string ss="aa我我我aabb";
    cairo_show_text (cr, ss.c_str());

    //cout<<mystring.c_str();
    //cout<<my1.c_str();
    //    cairo_surface_write_to_png (surface, "image.png");

    cairo_destroy (cr);
    //cairo_surface_destroy (surface);
    return surface;
}




void OfdView::test_cairo()
{

    if(!this->m_ofdEngine)
        return;
    qDebug() << "page count:"<< this->m_ofdEngine->m_pages.size();
    for(int i=0;i<this->m_ofdEngine->m_pages.size();i++)
    {

        cairo_surface_t* page =  this->m_ofdEngine->m_pages.at(i);
        QImage* image = new QImage(cairo_image_surface_get_data(page),
                                   cairo_image_surface_get_width(page),
                                   cairo_image_surface_get_height(page),
                                   QImage::Format_ARGB32);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));



        int width = cairo_image_surface_get_width(page);
        int height = cairo_image_surface_get_height(page);
        tmp_x = width;
        tmp_y = tmp_y + 20 + height;
        const QRectF pageRect(tmp_x,tmp_y,width,height);
        QGraphicsRectItem *rect = m_pageScene->addRect(pageRect, QPen(QBrush(Qt::black), 1)); // black border
        m_pageScene->addRect(pageRect, QPen(), QBrush(Qt::white)); // white background
        item->setOffset(tmp_x,tmp_y);
        this->m_pageScene->addItem(item);


//        this->m_pageScene->addRect(pageRect);
//        qDebug() << width << "height:"<<height;
    }
//    int iW = 2000;

//    int iH = 2000;


//    cairo_surface_t* surf = getcairsurface();

//    const QRectF pageRect(10,20,100,200);
//    const QRectF pageRect1(10,220,100,200);

//    m_pageScene->addRect(pageRect, QPen(QBrush(Qt::black), 1));
//    m_pageScene->addRect(pageRect1, QPen(QBrush(Qt::black), 1));
//    QImage* image = new QImage(cairo_image_surface_get_data(surf),
//                               cairo_image_surface_get_width(surf),
//                               cairo_image_surface_get_height(surf),
//                               QImage::Format_ARGB32);


//    //    QImage image("/Users/charles/Desktop/dd/qingyun_createfiles_1m_50.f.png");

//    ////    QImage image(iW, iH, QImage::Format_ARGB32);
//    //    QPainter painter(this);
//    //    QPixmap pixmapToShow = QPixmap::fromImage( image.scaled(size(), Qt::KeepAspectRatio) );
//    //    painter.drawPixmap(0,0, pixmapToShow);
//    //    unsigned char* pData =image.bits();

//    //    int iLineStride = image.bytesPerLine();

//    //    cairo_surface_t * pCairoSurface = cairo_image_surface_create_for_data(pData,CAIRO_FORMAT_ARGB32,iW,iH, iLineStride);

//    //    cairo_t* pCairoContext = cairo_create(pCairoSurface);

//    //    cairo_surface_destroy(pCairoSurface);
//    //    if(pCairoSurface)
//    //    {
//    //        cairo_set_source_rgb (pCairoContext, 0.627, 0, 0);
//    //        cairo_select_font_face (pCairoContext, "Simsun",
//    //                                CAIRO_FONT_SLANT_NORMAL,
//    //                                CAIRO_FONT_WEIGHT_NORMAL);

//    //        cairo_set_source_rgb(pCairoContext, 0.5, 0.4, 0.3);
//    //        cairo_set_font_size (pCairoContext, 24.0);
//    //        cairo_move_to (pCairoContext, 10.0, 34.0);

//    //        std::string ss="hello world";
//    //        cairo_show_text (pCairoContext, ss.c_str());
//    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
////    m_pageScene->addItem(item);
//    //        cairo_destroy (pCairoContext);
//    //    }


}

OfdView::~OfdView()
{

}

