#include "documentview.h"
#include "model.h"
#include "pluginhandler.h"
#include "pageitem.h"
using namespace ofdreader;

DocumentView::DocumentView(QWidget *parent):
    QGraphicsView(parent)
{

}


QString DocumentView::title() const
{
    return "this is title";
}


void DocumentView::preparePages()
{
    m_pageItems.clear();
    m_pageItems.reserve(m_pages.count());

    for(int index = 0; index < m_pages.count(); ++index)
    {
        PageItem* page = new PageItem(m_pages.at(index), index);

//        page->setRubberBandMode(m_rubberBandMode);
        scene()->addItem(page);
        m_pageItems.append(page);
    }
}

void DocumentView::prepareDocument(Model::IDocument* document, const QVector<Model::IPage*>& pages)
{
    m_pages = pages;
    delete m_document;
    m_document = document;
    preparePages();
}

bool DocumentView::open(const QString& filePath)
{

    Model::IDocument* document = PluginHandler::instance()->loadDocument(filePath);

    if(document != 0)
    {
        QVector< Model::IPage* > pages;

        //        if(!checkDocument(filePath, document, pages))
        //        {
        //            delete document;
        //            qDeleteAll(pages);

        //            return false;
        //        }

        //        m_fileInfo.setFile(filePath);
        //        m_wasModified = false;

        //        m_currentPage = 1;

        //        m_past.clear();
        //        m_future.clear();

        prepareDocument(document, pages);

        //        loadDocumentDefaults();

        //        adjustScrollBarPolicy();

        //        prepareScene();
        //        prepareView();

        //        prepareThumbnailsScene();

        //        emit documentChanged();

        //        emit numberOfPagesChanged(m_pages.count());
        //        emit currentPageChanged(m_currentPage);

        //        emit canJumpChanged(false, false);

        //        emit continuousModeChanged(m_continuousMode);
        //        emit layoutModeChanged(m_layout->layoutMode());
        //        emit rightToLeftModeChanged(m_rightToLeftMode);
    }

    return document != 0;
}
