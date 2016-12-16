#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H
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

        void prepareDocument(Model::IDocument* document, const QVector<Model::IPage*>& pages);
        void preparePages();
        Model::IDocument* m_document;
        QVector<Model::IPage*> m_pages;


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
