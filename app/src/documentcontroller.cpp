#include "include/documentcontroller.h"
#include <libofdengine.h>
//#include <cairo/cairo.h>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QPen>
#include <QDebug>
DocumentController::DocumentController(QObject *parent) : QObject(parent)
{
    _page = -1;
//    _scaleMode = ScaleFactorMode;
//    _displayMode = PagingMode;
//    _scaleFactor = 1.0;
    _displayMode  = PagingMode;
}


bool DocumentController::loadFile(const QString &filePath)
{
    _page = 0;
//    m_OfdEngine = new libOfdEngine();
//    m_OfdEngine->load("ss");
////    m_OfdEngine->loadtest();
//    emit documentChanged(filePath);
//    emit pageChanged(_page);
    return false;
}

int DocumentController::pageCount() const
{
//    _page = 1;
//    return m_OfdEngine->m_pages_all.count();
    return 2;
}
qreal DocumentController::pageWidth() const
{
//    return m_OfdEngine->page(_page-1)->Wdith();
    return 0.0f;
}
qreal DocumentController::pageHeight() const
{
//    return m_OfdEngine->page(_page-1)->Height();
    return 100.0f;
}

QImage DocumentController::renderPage(const qreal &resolutionX, const qreal &resolutionY) const
{
//    cairo_surface_t* page =  this->m_OfdEngine->m_pages.at(i);
//    QImage* image = new QImage(cairo_image_surface_get_data(page),
//                               cairo_image_surface_get_width(page),
//                               cairo_image_surface_get_height(page),
//                               QImage::Format_ARGB32);
//    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));



//    int width = cairo_image_surface_get_width(page);
//    int height = cairo_image_surface_get_height(page);
//    tmp_x = width;
//    tmp_y = tmp_y + 20 + height;
//    const QRectF pageRect(tmp_x,tmp_y,width,height);
//    QGraphicsRectItem *rect = m_pageScene->addRect(pageRect, QPen(QBrush(Qt::black), 1)); // black border
//    m_pageScene->addRect(pageRect, QPen(), QBrush(Qt::white)); // white background
//    item->setOffset(tmp_x,tmp_y);
//    this->m_pageScene->addItem(item);
    QImage q = QImage();

    return QImage(1,1,QImage::Format_ARGB32);

}

QImage DocumentController::renderPage(const int &page, const qreal &resolutionX, const qreal &resolutionY) const
{
    return QImage(1,1,QImage::Format_ARGB32);
}



void DocumentController::nextPage() {
    qDebug()<<"Document Controller NextPage";
    switch(_displayMode) {
    case PagingMode:
    case ScrollingMode:
        if( _page <= pageCount()-1) {
            _page++;
            qDebug()<<"page:"<<_page;
            emit pageChanged(_page);
        }
        break;
    case DoublePagingMode:
    case DoubleScrollingMode:
        if( _page <= pageCount()-2) {
            _page += 2;
            emit pageChanged(_page);
        }
        break;
    }
}
