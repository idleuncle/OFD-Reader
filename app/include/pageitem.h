#ifndef PAGEITEM_H
#define PAGEITEM_H

#include <QGraphicsObject>
class PageItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit PageItem();

    QRectF boundingRect() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*);

    void setRect(QRectF rect){m_rect = rect;}



    inline void paintPage(QPainter* painter, const QRectF& exposedRect) const;
private:
    QRectF m_rect;
    QRectF m_boundingRect;
};

#endif // PAGEITEM_H
