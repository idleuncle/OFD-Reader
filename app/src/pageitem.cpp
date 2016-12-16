#include "pageitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
using namespace ofdreader;

PageItem::PageItem()
{

}



PageItem::PageItem(Model::IPage* page, int index, PaintMode paintMode /*= DefaultMode*/, QGraphicsItem* parent/* = 0*/)
{

}

QRectF PageItem::boundingRect() const
{
    if(m_boundingRect.isNull())
    {
        return QRectF(-25, -25, 50, 50);
    }
    return m_boundingRect;
}

void PageItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{

    qDebug()<< option->exposedRect;
    //paint ofd/pdf
//    paintPage(paiter,option->);
    paintPage(painter,option->exposedRect);


//    // 反走样
//    painter->setRenderHint(QPainter::Antialiasing, true);

//    // 脸
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(Qt::yellow);
//    painter->drawEllipse(m_rect);

////    painter->setPen(Qt::NoPen);
////    painter->setBrush(Qt::yellow);
////    painter->drawEllipse(m_rect);

}

inline void PageItem::paintPage(QPainter* painter, const QRectF& exposedRect) const
{
//        painter->setPen(Qt::NoPen);
//        painter->setBrush(Qt::yellow);
//        painter->drawEllipse(exposedRect);
    return;
}
