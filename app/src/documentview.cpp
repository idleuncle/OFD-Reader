#include "documentview.h"
#include "model.h"
#include "pluginhandler.h"
#include "pageitem.h"
#include "global.h"
#include "renderparam.h"
#include "documentlayout.h"
#include "typedef.h"
using namespace ofdreader;

DocumentView::DocumentView(QWidget *parent):
    QGraphicsView(parent),
    m_document(0),
    m_pages(),
    m_currentPage(-1),
    m_firstPage(-1),
    m_layout(new SinglePageLayout),
    m_scaleMode(ScaleFactorMode),
    m_scaleFactor(1.0),
    m_rotation(RotateBy0),
    m_renderFlags(0),
    m_pageItems()

{
    m_document = NULL;


    setScene(new QGraphicsScene(this));
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

void DocumentView::saveLeftAndTop(qreal& left, qreal& top) const
{
    const PageItem* page = m_pageItems.at(m_currentPage - 1);
    const QRectF boundingRect = page->uncroppedBoundingRect().translated(page->pos());

    const QPointF topLeft = mapToScene(viewport()->rect().topLeft());

    left = (topLeft.x() - boundingRect.x()) / boundingRect.width();
    top = (topLeft.y() - boundingRect.y()) / boundingRect.height();
}

void DocumentView::setScaleFactor(qreal scaleFactor)
{
    m_scaleFactor = scaleFactor;

    if(m_scaleMode == ScaleFactorMode)
    {
        qreal left = 0.0, top = 0.0;
        saveLeftAndTop(left, top);

        prepareScene();
        prepareView(left, top);
    }

//    emit scaleFactorChanged(m_scaleFactor);
}

void DocumentView::prepareDocument(Model::IDocument* document, const QVector<Model::IPage*>& pages)
{
    qDeleteAll(m_pageItems);

    qDeleteAll(m_pages);

    m_pages = pages;
    delete m_document;

    m_document = document;
    preparePages();
}

void DocumentView::prepareBackground()
{
    QColor backgroundColor = QColor(Qt::GlobalColor::gray);

    scene()->setBackgroundBrush(QBrush(backgroundColor));
//    m_thumbnailsScene->setBackgroundBrush(QBrush(backgroundColor));
}

bool DocumentView::checkDocument(const QString& filePath, Model::IDocument* document, QVector<Model::IPage*>& pages)
{
//    if(document->isLocked())
//    {
//        QString password = QInputDialog::getText(this, tr("Unlock %1").arg(QFileInfo(filePath).completeBaseName()), tr("Password:"), QLineEdit::Password);

//        if(document->unlock(password))
//        {
//            return false;
//        }
//    }

    const int numberOfPages = document->numberOfPages();

    if(numberOfPages == 0)
    {
        qWarning() << "No pages were found in document at" << filePath;

        return false;
    }

    pages.reserve(numberOfPages);

    for(int index = 0; index < numberOfPages; ++index)
    {
        Model::IPage* page = document->page(index);

        if(page == 0)
        {
            qWarning() << "No page" << index << "was found in document at" << filePath;

            return false;
        }

        pages.append(page);
    }

    return true;
}

DocumentView::~DocumentView()
{
    if(m_document)
    {
        delete m_document;
        m_document = NULL;
    }
}


void DocumentView::prepareScene()
{
    // prepare render parameters and adjust scale factor


    //RenderParam renderParam(logicalDpiX(), logicalDpiY(), 1.0,scaleFactor(), rotation());
    RenderParam renderParam(logicalDpiX(), logicalDpiY(), 1.0,scaleFactor(), rotation(),renderFlags());

#if QT_VERSION >= QT_VERSION_CHECK(5,1,0)

//    if(s_settings->pageItem().useDevicePixelRatio())
//    {
//        renderParam.setDevicePixelRatio(devicePixelRatio());
//    }

#endif // QT_VERSION

    const qreal visibleWidth = m_layout->visibleWidth(viewport()->width());
    const qreal visibleHeight = m_layout->visibleHeight(viewport()->height());

    foreach(PageItem* page, m_pageItems)
    {
        const QSizeF displayedSize = page->displayedSize(renderParam);

        if(m_scaleMode == FitToPageWidthMode)
        {
//            adjustScaleFactor(renderParam, visibleWidth / displayedSize.width());
        }
        else if(m_scaleMode == FitToPageSizeMode)
        {
//            adjustScaleFactor(renderParam, qMin(visibleWidth / displayedSize.width(), visibleHeight / displayedSize.height()));
        }

        page->setRenderParam(renderParam);
    }

//    // prepare layout

    qreal left = 0.0;
    qreal right = 0.0;
//    qreal height = 0.0f;
    qreal height = PAGESPACE;//s_settings->documentView().pageSpacing();

    m_layout->prepareLayout(m_pageItems, m_rightToLeftMode,
                            left, right, height);

    qDebug()<<"left:"<<left<<"right:"<<right<<"height:"<<height;
    scene()->setSceneRect(left, 0.0, right - left, height);
}

void DocumentView::prepareView(qreal newLeft, qreal newTop, bool forceScroll, int scrollToPage)
{
    const QRectF sceneRect = scene()->sceneRect();

    qreal top = sceneRect.top();
    qreal height = sceneRect.height();

    int horizontalValue = 0;
    int verticalValue = 0;

    scrollToPage = scrollToPage != 0 ? scrollToPage : m_currentPage;

//    const int highlightIsOnPage = m_currentResult.isValid() ? pageOfResult(m_currentResult) : 0;
//    const bool highlightCurrentThumbnail = s_settings->documentView().highlightCurrentThumbnail();

//    for(int index = 0; index < m_pageItems.count(); ++index)
//    {
//        PageItem* page = m_pageItems.at(index);

//        if(m_continuousMode)
//        {
//            page->setVisible(true);
//        }
//        else
//        {
//            if(m_layout->leftIndex(index) == m_currentPage - 1)
//            {
//                page->setVisible(true);

//                const QRectF boundingRect = page->boundingRect().translated(page->pos());

//                top = boundingRect.top() - s_settings->documentView().pageSpacing();
//                height = boundingRect.height() + 2.0 * s_settings->documentView().pageSpacing();
//            }
//            else
//            {
//                page->setVisible(false);

//                page->cancelRender();
//            }
//        }

//        if(index == scrollToPage - 1)
//        {
//            const QRectF boundingRect = page->uncroppedBoundingRect().translated(page->pos());

//            horizontalValue = qFloor(boundingRect.left() + newLeft * boundingRect.width());
//            verticalValue = qFloor(boundingRect.top() + newTop * boundingRect.height());
//        }

//        if(index == highlightIsOnPage - 1)
//        {
//            m_highlight->setPos(page->pos());
//            m_highlight->setTransform(page->transform());

//            page->stackBefore(m_highlight);
//        }

//        m_thumbnailItems.at(index)->setHighlighted(highlightCurrentThumbnail && (index == m_currentPage - 1));
//    }

//    setSceneRect(sceneRect.left(), top, sceneRect.width(), height);

//    if(!forceScroll && s_settings->documentView().minimalScrolling())
//    {
//        setValueIfNotVisible(horizontalScrollBar(), horizontalValue);
//        setValueIfNotVisible(verticalScrollBar(), verticalValue);
//    }
//    else
//    {
//        horizontalScrollBar()->setValue(horizontalValue);
//        verticalScrollBar()->setValue(verticalValue);
//    }

    viewport()->update();
}


bool DocumentView::open(const QString& filePath)
{

    Model::IDocument* document = PluginHandler::instance()->loadDocument(filePath);

    if(document != 0)
    {
        QVector< Model::IPage* > pages;

                if(!checkDocument(filePath, document, pages))
                {
                    delete document;
                    qDeleteAll(pages);

                    return false;
                }

        //        m_fileInfo.setFile(filePath);
        //        m_wasModified = false;

                m_currentPage = 1;

        //        m_past.clear();
        //        m_future.clear();

        prepareDocument(document, pages);

        //        loadDocumentDefaults();

        //        adjustScrollBarPolicy();

                prepareScene();
                prepareView();
                prepareBackground();

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
