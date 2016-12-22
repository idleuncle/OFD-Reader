#include "pageitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
using namespace ofdreader;


PageItem::PageItem(Model::IPage* page, int index, PaintMode paintMode /*= DefaultMode*/, QGraphicsItem* parent/* = 0*/):
    QGraphicsObject(parent),
    m_page(page),
    m_boundingRect(),
    m_cropRect(),
    m_rect(),
    m_size(page->size()),
    m_index(index),
    m_paintMode(paintMode),
    m_renderParam(),
    m_transform()
{
//    page->render()




    prepareGeometry();
}

QRectF PageItem::boundingRect() const
{
    if(m_cropRect.isNull())
    {
        return m_boundingRect;
    }

    QRectF boundingRect;

    boundingRect.setLeft(m_boundingRect.left() + m_cropRect.left() * m_boundingRect.width());
    boundingRect.setTop(m_boundingRect.top() + m_cropRect.top() * m_boundingRect.height());
    boundingRect.setWidth(m_cropRect.width() * m_boundingRect.width());
    boundingRect.setHeight(m_cropRect.height() * m_boundingRect.height());

    return boundingRect;
}

void PageItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
//    painter->drawRect(QRect(10,20,30,50));
    paintPage(painter, option->exposedRect);


}


void PageItem::run()
{
//#define CANCELLATION_POINT if(testCancellation()) { finish(); return; }

//    CANCELLATION_POINT

//    QImage image;
//    QRectF cropRect;

//#if QT_VERSION >= QT_VERSION_CHECK(5,1,0)

//    const qreal devicePixelRatio = m_renderParam.devicePixelRatio();

//    const QRect rect =
//            qFuzzyCompare(1.0, devicePixelRatio)
//            ? m_rect
//            : QTransform().scale(devicePixelRatio, devicePixelRatio).mapRect(m_rect);

//#else

//    const QRect& rect = m_rect;

//#endif // QT_VERSION

//    image = m_page->render(scaledResolutionX(m_renderParam), scaledResolutionY(m_renderParam),
//                           m_renderParam.rotation(), rect);

//#if QT_VERSION >= QT_VERSION_CHECK(5,1,0)

//    image.setDevicePixelRatio(devicePixelRatio);

//#endif // QT_VERSION

//    if(m_renderParam.darkenWithPaperColor())
//    {
//        CANCELLATION_POINT

//        composeWithColor(QPainter::CompositionMode_Darken, s_settings->pageItem().paperColor(), image);
//    }
//    else if(m_renderParam.lightenWithPaperColor())
//    {
//        CANCELLATION_POINT

//        composeWithColor(QPainter::CompositionMode_Lighten, s_settings->pageItem().paperColor(), image);
//    }

//    if(m_renderParam.trimMargins())
//    {
//        CANCELLATION_POINT

//        cropRect = trimMargins(s_settings->pageItem().paperColor().rgb() | alphaMask, image);
//    }

//    if(m_renderParam.convertToGrayscale())
//    {
//        CANCELLATION_POINT

//        convertToGrayscale(image);
//    }

//    if(m_renderParam.invertColors())
//    {
//        CANCELLATION_POINT

//        image.invertPixels();
//    }

//    CANCELLATION_POINT

//    s_dispatcher->imageReady(m_parent,
//                             m_renderParam,
//                             m_rect, m_prefetch,
//                             image, cropRect);

//    finish();

//#undef CANCELLATION_POINT
}


qreal scaledResolutionX(const RenderParam& renderParam)
{
    return renderParam.devicePixelRatio()
            * renderParam.resolutionX()
            * renderParam.scaleFactor();
}

qreal scaledResolutionY(const RenderParam& renderParam)
{
    return renderParam.devicePixelRatio()
            * renderParam.resolutionY()
            * renderParam.scaleFactor();
}

inline void PageItem::paintPage(QPainter* painter, const QRectF& exposedRect) const
{
//    if(s_settings->pageItem().decoratePages() && !presentationMode())
       {
           // background

           QColor paperColor = Qt::GlobalColor::white;//s_settings->pageItem().paperColor();

           if(m_renderParam.invertColors())
           {
               paperColor.setRgb(~paperColor.rgb());
           }

           painter->fillRect(m_boundingRect, QBrush(paperColor));

           const qreal devicePixelRatio = m_renderParam.devicePixelRatio();

           const QRect rect =
                   qFuzzyCompare(1.0, devicePixelRatio)
                   ? m_rect
                   : QTransform().scale(devicePixelRatio, devicePixelRatio).mapRect(m_rect);
           QImage image = m_page->render(scaledResolutionX(m_renderParam), scaledResolutionY(m_renderParam),
                                  m_renderParam.rotation(), rect);


            painter->drawPixmap(m_rect.topLeft()+exposedRect.topLeft(),QPixmap::fromImage(image));
            // drow border
            painter->save();

            painter->setClipping(false);

            painter->drawRect(m_renderParam.trimMargins() ? PageItem::boundingRect() : PageItem::uncroppedBoundingRect());

            painter->restore();

       }

}


void PageItem::refresh(bool keepObsoletePixmaps, bool dropCachedPixmaps)
{
//    if(!useTiling())
//    {
//        m_tileItems.first()->refresh(keepObsoletePixmaps);
//    }
//    else
//    {
//        foreach(TileItem* tile, m_tileItems)
//        {
//            tile->refresh(keepObsoletePixmaps);
//        }
//    }

//    if(!keepObsoletePixmaps)
//    {
//        prepareGeometryChange();

//        m_cropRect = QRectF();
//    }

//    if(dropCachedPixmaps)
//    {
//        TileItem::dropCachedPixmaps(this);
//    }

    update();
}


void PageItem::setRenderParam(const RenderParam& renderParam)
{
    if(m_renderParam != renderParam)
    {
        const bool resolutionChanged = m_renderParam.resolutionX() != renderParam.resolutionX()
                || m_renderParam.resolutionY() != renderParam.resolutionY()
                || !qFuzzyCompare(m_renderParam.devicePixelRatio(), renderParam.devicePixelRatio())
                || !qFuzzyCompare(m_renderParam.scaleFactor(), renderParam.scaleFactor());

        const bool rotationChanged = m_renderParam.rotation() != renderParam.rotation();

        const RenderFlags changedFlags = m_renderParam.flags() ^ renderParam.flags();

        refresh(!rotationChanged && changedFlags == 0);

        m_renderParam = renderParam;

        if(resolutionChanged || rotationChanged)
        {
            prepareGeometryChange();
            prepareGeometry();
        }

        if(changedFlags.testFlag(TrimMargins))
        {
            setFlag(QGraphicsItem::ItemClipsToShape, m_renderParam.trimMargins());
        }
    }
}


QSizeF PageItem::displayedSize(const RenderParam& renderParam) const
{
    const bool rotationChanged = m_renderParam.rotation() != renderParam.rotation();

    const bool flagsChanged = m_renderParam.flags() != renderParam.flags();

    const bool useCropRect = !m_cropRect.isNull() && !rotationChanged && !flagsChanged;

    const qreal cropWidth = useCropRect ? m_cropRect.width() : 1.0;
    const qreal cropHeight = useCropRect ? m_cropRect.height() : 1.0;

    switch(renderParam.rotation())
    {
    default:
    case RotateBy0:
    case RotateBy180:
        return QSizeF(renderParam.resolutionX() / 72.0 * cropWidth * m_size.width(),
                      renderParam.resolutionY() / 72.0 * cropHeight * m_size.height());
    case RotateBy90:
    case RotateBy270:
        return QSizeF(renderParam.resolutionX() / 72.0 * cropHeight * m_size.height(),
                      renderParam.resolutionY() / 72.0 * cropWidth * m_size.width());
    }
}

void PageItem::prepareGeometry()
{
    m_transform.reset();
    // 缩放
//    qDebug()<<"m_renderParam.resolutionX() * m_renderParam.scaleFactor() / 72.0:"<<
//              m_renderParam.resolutionX() * m_renderParam.scaleFactor() / 72.0;
//    qDebug()<<"m_renderParam.resolutionY() * m_renderParam.scaleFactor() / 72.0:"<<
//              m_renderParam.resolutionY() * m_renderParam.scaleFactor() / 72.0;

    qDebug()<<"m_renderParam.resolutionX():"<<m_renderParam.resolutionX();
    qDebug()<<"m_renderParam.scaleFactor():"<<m_renderParam.scaleFactor();
    m_transform.scale(m_renderParam.resolutionX() * m_renderParam.scaleFactor() / 72.0,
                      m_renderParam.resolutionY() * m_renderParam.scaleFactor() / 72.0);

    qDebug()<<"m_renderParam.rotation()"<<m_renderParam.rotation();
    switch(m_renderParam.rotation())
    {
    default:
    case RotateBy0:
        break;
    case RotateBy90:
        m_transform.rotate(90.0);
        break;
    case RotateBy180:
        m_transform.rotate(180.0);
        break;
    case RotateBy270:
        m_transform.rotate(270.0);
        break;
    }

    m_normalizedTransform = m_transform;
    m_normalizedTransform.scale(m_size.width(), m_size.height());


    m_boundingRect = m_transform.mapRect(QRectF(QPointF(), m_size));

    m_boundingRect.setWidth(qRound(m_boundingRect.width()));
    m_boundingRect.setHeight(qRound(m_boundingRect.height()));
    qDebug()<<"m_boundingRect:"<<m_boundingRect;


//    prepareTiling();

//    updateAnnotationOverlay();
//    updateFormFieldOverlay();
}
