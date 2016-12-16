#ifndef PAGEITEM_H
#define PAGEITEM_H

#include <QGraphicsObject>
#include "model.h"
using namespace ofdreader::Model;
namespace ofdreader
{

class PageItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum PaintMode
    {
        DefaultMode, //默认
        PresentationMode, //幻灯片模式
        ThumbnailMode //缩略图模式
    };
    explicit PageItem();
    PageItem(Model::IPage* page, int index, PaintMode paintMode = DefaultMode, QGraphicsItem* parent = 0);

    QRectF boundingRect() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*);

    void setRect(QRectF rect){m_rect = rect;}



    inline void paintPage(QPainter* painter, const QRectF& exposedRect) const;
private:
    QRectF m_rect;
    QRectF m_boundingRect;
};

}

#endif // PAGEITEM_H
