#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H
#include "global.h"
#include <QGraphicsView>


namespace ofdreader
{
    class PageItem;
    namespace Model
    {
        class IPage;
        class IDocument;
    }


    class DocumentView : public  QGraphicsView
    {
        Q_OBJECT
    public:
        explicit DocumentView(QWidget *parent = 0);
        virtual ~DocumentView();

        bool checkDocument(const QString& filePath, Model::IDocument* document, QVector<Model::IPage*>& pages);

        void prepareDocument(Model::IDocument* document, const QVector<Model::IPage*>& pages);
        void preparePages();
        void prepareScene();
        void prepareView(qreal newLeft = 0.0, qreal newTop = 0.0, bool forceScroll = true, int scrollToPage = 0);


        ScaleMode scaleMode() const { return m_scaleMode; }
            void setScaleMode(ScaleMode scaleMode);

            qreal scaleFactor() const { return m_scaleFactor; }
            void setScaleFactor(qreal scaleFactor);

            Rotation rotation() const { return m_rotation; }
            void setRotation(Rotation rotation);

            RenderFlags renderFlags() const { return m_renderFlags; }
                void setRenderFlags(RenderFlags renderFlags);
                void setRenderFlag(RenderFlag renderFlag, bool enabled = true);


        Model::IDocument* m_document;
        QVector<Model::IPage*> m_pages;


        bool m_continuousMode;
            bool m_rightToLeftMode;
            ScaleMode m_scaleMode;
            qreal m_scaleFactor;
            Rotation m_rotation;
            RenderFlags m_renderFlags;


        QString title() const;

        bool open(const QString& filePath);

        QVector<PageItem*> m_pageItems;

        int numberOfPages() const { return m_pages.count(); }
        int currentPage() const { return m_currentPage; }

        int m_currentPage;
        int m_firstPage;
    };
}

#endif // DOCUMENTVIEW_H
