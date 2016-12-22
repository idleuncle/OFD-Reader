#ifndef PAGEITEM_H
#define PAGEITEM_H

#include <QGraphicsObject>
#include "model.h"
#include "renderparam.h"
using namespace ofdreader::Model;
namespace ofdreader
{

class PageItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum PaintMode
    {
        //默认
        DefaultMode,
        //幻灯片模式
        PresentationMode,
        //缩略图模式
        ThumbnailMode
    };
    PageItem(Model::IPage* page, int index, PaintMode paintMode = DefaultMode, QGraphicsItem* parent = 0);


    // 需要重boundingRect paint
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*);

    QSizeF displayedSize() const { return displayedSize(renderParam()); }

    const RenderParam& renderParam() const { return m_renderParam; }
    void setRenderParam(const RenderParam& renderParam);

    const QTransform& transform() const { return m_transform; }
    const QTransform& normalizedTransform() const { return m_normalizedTransform; }


    const QRectF& uncroppedBoundingRect() const { return m_boundingRect; }
    QSizeF displayedSize(const RenderParam& renderParam) const;



    void setRect(QRect rect){m_rect = rect;}

    RenderParam m_renderParam;

    // 处理transform, 旋转等
    void prepareGeometry();

    inline void paintPage(QPainter* painter, const QRectF& exposedRect) const;
    void run();
public slots:
    void refresh(bool keepObsoletePixmaps = false, bool dropCachedPixmaps = false);



private:
    Q_DISABLE_COPY(PageItem)

    Model::IPage* m_page;
    QSizeF m_size;
    QRect m_rect;
    QRectF m_boundingRect;

    QRectF m_cropRect;

    QTransform m_transform;
    QTransform m_normalizedTransform;

    int m_index;
    PaintMode m_paintMode;
};

}

#endif // PAGEITEM_H
