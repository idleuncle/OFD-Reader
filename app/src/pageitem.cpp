#include "pageitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
using namespace ofdreader;

PageItem::PageItem()
{

}



PageItem::PageItem(Model::IPage* page, int index, PaintMode paintMode /*= DefaultMode*/, QGraphicsItem* parent/* = 0*/):
    QGraphicsObject(parent),
    m_boundingRect()
{

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

    paintPage(painter, option->exposedRect);


}

inline void PageItem::paintPage(QPainter* painter, const QRectF& exposedRect) const
{
//    if(s_settings->pageItem().decoratePages() && !presentationMode())
       {
           // background

           QColor paperColor = Qt::GlobalColor::red;//s_settings->pageItem().paperColor();

           if(m_renderParam.invertColors())
           {
               paperColor.setRgb(~paperColor.rgb());
           }

           painter->fillRect(m_boundingRect, QBrush(paperColor));
       }
    return;

//       // tiles

//       if(!useTiling())
//       {
//           TileItem* tile = m_tileItems.first();

//           if(tile->paint(painter, m_boundingRect.topLeft()))
//           {
//               tile->dropPixmap();
//           }
//       }
//       else
//       {
//           const QRectF& translatedExposedRect = exposedRect.translated(-m_boundingRect.topLeft());

//           foreach(TileItem* tile, m_tileItems)
//           {
//               const bool intersects = translatedExposedRect.intersects(tile->rect());
//               const bool contains = m_exposedTileItems.contains(tile);

//               if(intersects && !contains)
//               {
//                   m_exposedTileItems.insert(tile);
//               }
//               else if(!intersects && contains)
//               {
//                   m_exposedTileItems.remove(tile);

//                   tile->cancelRender();
//               }
//           }

//           bool allExposedPainted = true;

//           foreach(TileItem* tile, m_exposedTileItems)
//           {
//               if(!tile->paint(painter, m_boundingRect.topLeft()))
//               {
//                   allExposedPainted = false;
//               }
//           }

//           if(allExposedPainted)
//           {
//               foreach(TileItem* tile, m_exposedTileItems)
//               {
//                   tile->dropPixmap();
//               }
//           }
//       }

//       if(s_settings->pageItem().decoratePages() && !presentationMode())
//       {
//           // border

//           painter->save();

//           painter->setClipping(false);

//           painter->drawRect(m_renderParam.trimMargins() ? PageItem::boundingRect() : PageItem::uncroppedBoundingRect());

//           painter->restore();
//       }

}
