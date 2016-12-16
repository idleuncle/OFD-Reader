#include "ofdmainwindow.h"
#include <QVBoxLayout>
#include <QDockWidget>
#include <QToolButton>
#include <QPushButton>
#include <QFileDialog>
#include "documentview.h"
using namespace ofdreader;
OfdMainWindow::OfdMainWindow(QWidget *parent) : QMainWindow(parent)
{
//    m_mainToolbar = NULL;
    m_fileOpenAction = NULL;
    m_fileToolbar = NULL;
    m_editToolbar = NULL;
    m_viewToolbar = NULL;

    this->init();
//    m_mainToolbar1 = new QToolBar("sss",this);
    return ;
    QWidget *mainWidget = new QWidget(this);
//    m_OfdEngine = new libOfdEngine();
//    m_OfdEngine->loadtest();

//    m_ofdView = new OfdView(m_OfdEngine,this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(m_ofdView);



    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
//    m_ofdView->setofdengine(m_OfdEngine);


    //初始化
    this->createActions();


    QDockWidget *leftDock=new QDockWidget("left",this);

    leftDock->setAllowedAreas(Qt::LeftDockWidgetArea| Qt::BottomDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

}


OfdMainWindow::~OfdMainWindow()
{
    if(m_fileOpenAction)
    {
        delete m_fileOpenAction;
        m_fileOpenAction = NULL;
    }
//    if(m_mainToolbar)
//    {
//        delete m_mainToolbar;
//        m_mainToolbar = NULL;
//    }


}


int OfdMainWindow::addTab(DocumentView* tab)
{
//    const int index = s_settings->mainWindow().newTabNextToCurrentTab() ?
//                    m_tabWidget->insertTab(m_tabWidget->currentIndex() + 1, tab, tab->title()) :
//                    m_tabWidget->addTab(tab, tab->title());

    const int index = m_tabWidget->addTab(tab, tab->title());
//        m_tabWidget->setTabToolTip(index, tab->fileInfo().absoluteFilePath());
        m_tabWidget->setCurrentIndex(index);

        return index;
}

void OfdMainWindow::closeTab(DocumentView* tab)
{

}

QList<DocumentView*> OfdMainWindow::tabs() const
{
    QList<DocumentView*> tabs;

    for(int index = 0, count = m_tabWidget->count(); index < count; ++index)
    {
//        tabs.append(tab(index));
//        tabs.append(qobject_cast<DocumentView*>(m_tabWidget->widget(index)));

    }

    return tabs;
}

//void OfdMainWindow::createActions()
//{

////    m_mainToolbar = this->addToolBar(tr("Tool Bar"));
////    m_fileOpenAction = new QAction(QIcon(":/icons/document-open.svg"),tr("&Open...", "Action: open file"), this);
////    m_fileOpenAction->setObjectName("file_open");

////    m_fileSaveCopyAction = new QAction(QIcon(":/icons/document-save.svg"),tr("&Open...", "Action: open file"), this);
////    m_fileSaveCopyAction->setObjectName("file_save");

////    connect(m_fileOpenAction, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
////    connect(m_fileSaveCopyAction, SIGNAL(triggered()), this, SLOT(slotSaveCopy()));


//    // 上一页/下一页
////    QWidget *navBar = new QWidget(m_mainToolbar);
////    QHBoxLayout *navLayout = new QHBoxLayout;
////    navBar->setLayout(navLayout);
////    QToolButton *navPrevBtn = new QToolButton(navBar);
////    navPrevBtn->setIcon(QIcon(":/icons/go-previous.svg"));
////    navPrevBtn->setIconSize(QSize(40,40));
////    connect(navPrevBtn,SIGNAL( clicked()), this, SLOT(slotGoToPreviousPage()));
////    QToolButton *navNextBtn = new QToolButton(navBar);
////    navNextBtn->setIcon(QIcon(":/icons/go-next.svg"));
////    navNextBtn->setIconSize(QSize(40,40));
////    connect(navNextBtn,SIGNAL( clicked()), this, SLOT(slotGoToNextPage()));

////    navLayout->addWidget(navPrevBtn);
////    navLayout->addWidget(navNextBtn);





////    m_mainToolbar->addAction(m_fileOpenAction);
////    m_mainToolbar->addAction(m_fileSaveCopyAction);
////    m_mainToolbar->addWidget(navBar);



//}


void OfdMainWindow::slotOpenFile()
{
#ifdef _TEST_
        loadDocument("");
//        m_ofdView->test_cairo();
#else
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open OFD Document"), m_file, tr("OFD Documents (*.ofd)"));
    if (fileName.isEmpty()) {
        return;
    }
    loadDocument(fileName);
    m_ofdView->test_cairo();
    m_ofdView->viewport()->update();
#endif




}

void OfdMainWindow::on_open_triggered()
{
    QMessageBox::information(this,tr("ss"),tr("dd"));
}

void OfdMainWindow::on_open_new_tab_triggered()
{
//    const QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Open in new tab"));
    const QString filepath = "/tmp/sample0.ofd";
    openInNewTab(filepath);

}

bool OfdMainWindow::openInNewTab(const QString& filePath, int page, const QRectF& highlight, bool quiet)
{
    DocumentView* newTab = new DocumentView(this);

    if(newTab->open(filePath))
        {
////            s_settings->mainWindow().setOpenPath(newTab->fileInfo().absolutePath());
////            m_recentlyUsedMenu->addOpenAction(newTab->fileInfo());

////            const int index = addTab(newTab);

////            QAction* tabAction = new QAction(m_tabWidget->tabText(index), newTab);
////            connect(tabAction, SIGNAL(triggered()), SLOT(on_tabAction_triggered()));

////            tabAction->setData(true); // Flag action for search-as-you-type

////            m_tabsMenu->addAction(tabAction);

////            on_thumbnails_dockLocationChanged(dockWidgetArea(m_thumbnailsDock));

////            connect(newTab, SIGNAL(documentChanged()), SLOT(on_currentTab_documentChanged()));
////            connect(newTab, SIGNAL(documentModified()), SLOT(on_currentTab_documentModified()));

////            connect(newTab, SIGNAL(numberOfPagesChanged(int)), SLOT(on_currentTab_numberOfPagesChaned(int)));
////            connect(newTab, SIGNAL(currentPageChanged(int)), SLOT(on_currentTab_currentPageChanged(int)));

////            connect(newTab, SIGNAL(canJumpChanged(bool,bool)), SLOT(on_currentTab_canJumpChanged(bool,bool)));

////            connect(newTab, SIGNAL(continuousModeChanged(bool)), SLOT(on_currentTab_continuousModeChanged(bool)));
////            connect(newTab, SIGNAL(layoutModeChanged(LayoutMode)), SLOT(on_currentTab_layoutModeChanged(LayoutMode)));
////            connect(newTab, SIGNAL(rightToLeftModeChanged(bool)), SLOT(on_currentTab_rightToLeftModeChanged(bool)));
////            connect(newTab, SIGNAL(scaleModeChanged(ScaleMode)), SLOT(on_currentTab_scaleModeChanged(ScaleMode)));
////            connect(newTab, SIGNAL(scaleFactorChanged(qreal)), SLOT(on_currentTab_scaleFactorChanged(qreal)));
////            connect(newTab, SIGNAL(rotationChanged(Rotation)), SLOT(on_currentTab_rotationChanged(Rotation)));

////            connect(newTab, SIGNAL(linkClicked(int)), SLOT(on_currentTab_linkClicked(int)));
////            connect(newTab, SIGNAL(linkClicked(bool,QString,int)), SLOT(on_currentTab_linkClicked(bool,QString,int)));

////            connect(newTab, SIGNAL(renderFlagsChanged(qpdfview::RenderFlags)), SLOT(on_currentTab_renderFlagsChanged(qpdfview::RenderFlags)));

////            connect(newTab, SIGNAL(invertColorsChanged(bool)), SLOT(on_currentTab_invertColorsChanged(bool)));
////            connect(newTab, SIGNAL(convertToGrayscaleChanged(bool)), SLOT(on_currentTab_convertToGrayscaleChanged(bool)));
////            connect(newTab, SIGNAL(trimMarginsChanged(bool)), SLOT(on_currentTab_trimMarginsChanged(bool)));

////            connect(newTab, SIGNAL(compositionModeChanged(CompositionMode)), SLOT(on_currentTab_compositionModeChanged(CompositionMode)));

////            connect(newTab, SIGNAL(highlightAllChanged(bool)), SLOT(on_currentTab_highlightAllChanged(bool)));
////            connect(newTab, SIGNAL(rubberBandModeChanged(RubberBandMode)), SLOT(on_currentTab_rubberBandModeChanged(RubberBandMode)));

////            connect(newTab, SIGNAL(searchFinished()), SLOT(on_currentTab_searchFinished()));
////            connect(newTab, SIGNAL(searchProgressChanged(int)), SLOT(on_currentTab_searchProgressChanged(int)));

////            connect(newTab, SIGNAL(customContextMenuRequested(QPoint)), SLOT(on_currentTab_customContextMenuRequested(QPoint)));

////            newTab->show();

////            s_database->restorePerFileSettings(newTab);
////            scheduleSaveTabs();

////            newTab->jumpToPage(page, false);
////            newTab->setFocus();

////            if(!highlight.isNull())
////            {
////                newTab->temporaryHighlight(page, highlight);
////            }

////            return true;
////        }
////        else
////        {
////            delete newTab;

////            if(!quiet)
////            {
////                QMessageBox::warning(this, tr("Warning"), tr("Could not open '%1'.").arg(filePath));
////            }
        }

        return false;
}

void OfdMainWindow::on_previous_page_triggered()
{
    QMessageBox::information(this,tr("on_previous_page_triggered"),tr("on_previous_page_triggered"));
}

void OfdMainWindow::on_next_page_triggered()
{
    QMessageBox::information(this,tr("on_next_page_triggered"),tr("on_next_page_triggered"));
}

void OfdMainWindow::on_first_page_triggered()
{
    QMessageBox::information(this,tr("on_first_page_triggered"),tr("on_first_page_triggered"));
}

void OfdMainWindow::on_last_page_triggered()
{
    QMessageBox::information(this,tr("on_first_page_triggered"),tr("on_first_page_triggered"));
}

void OfdMainWindow::on_single_page_triggered()
{
    QMessageBox::information(this,tr("on_single_page_triggered"),tr("on_single_page_triggered"));
}

void OfdMainWindow::on_two_page_triggered()
{
    QMessageBox::information(this,tr("on_two_page_triggered"),tr("on_two_page_triggered"));
}

bool OfdMainWindow::loadDocument(const QString &filename)
{
//    return m_OfdEngine->load(filename);
    throw "todo loaddocument ";
}

void OfdMainWindow::slotSaveCopy()
{
    QMessageBox::information(this,tr("hmmmm"),tr("save file"));
}


void OfdMainWindow::init()
{
    this->createActions();
    this->createToolbar();
    this->createMainMenu();
    this->createDockers();
}


void OfdMainWindow::createMainMenu()
{

        m_fileMenu = menuBar()->addMenu(tr("&File"));
        m_fileMenu->addActions(QList<QAction*>()
                               << m_fileOpenAction
                               << m_fileNewTabAction
                               );


        m_editMenu = menuBar()->addMenu(tr("&Edit"));
        m_editMenu->addActions(QList<QAction*>()
                               << m_firstPageAction
                               << m_previousPageAction
                               << m_nextPageAction
                               << m_lastPageAction
                               );

        m_viewMenu = menuBar()->addMenu(tr("&View"));
        m_viewMenu->addActions(QList<QAction*>()
                               << m_singlePageAction
                               << m_twoPageAction
                               );

}

void OfdMainWindow::createDockers()
{

    m_outlineDock = new QDockWidget("outline", this);
    m_outlineDock->setObjectName("outline");
    m_outlineDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::LeftDockWidgetArea, m_outlineDock);

}

void OfdMainWindow::createActions()
{
    // file action
    m_fileOpenAction = new QAction(QIcon(":/icons/document-open.svg"),tr("&Open...", "Action: open file"), this);
    m_fileOpenAction->setObjectName("open");
    m_fileOpenAction->setShortcut(QKeySequence("ctrl+N"));

    m_fileNewTabAction = new QAction(QIcon(":/icons/tab-new.svg"),tr("&Open new tab...", "Action: open in new tab"), this);
    m_fileNewTabAction->setObjectName("open_new_tab");
    m_fileNewTabAction->setShortcut(QKeySequence("ctrl+T"));

    m_closeWindowsAction = new QAction(QIcon(":/icons/document-open.svg"),tr("&close windows", "Action: close windows"), this);
    m_closeWindowsAction->setObjectName("closewindow");
    m_closeWindowsAction->setShortcut(QKeySequence("ctrl+w"));


    connect(m_fileOpenAction, SIGNAL(triggered()), this, SLOT(on_open_triggered()));
    connect(m_fileNewTabAction, SIGNAL(triggered()), this, SLOT(on_open_new_tab_triggered()));


    // edit action
    m_previousPageAction = new QAction(QIcon(":/icons/go-previous.svg"),tr("&previous page...", "Action: previous page"), this);
    m_nextPageAction = new QAction(QIcon(":/icons/go-next.svg"),tr("&next page...", "Action: next page"), this);
    m_firstPageAction = new QAction(QIcon(":/icons/go-first.svg"),tr("&first page...", "Action: first page"), this);
    m_lastPageAction = new QAction(QIcon(":/icons/go-last.svg"),tr("&last page...", "Action: last page"), this);


    connect(m_previousPageAction, SIGNAL(triggered()), this, SLOT(on_previous_page_triggered()));
    connect(m_nextPageAction, SIGNAL(triggered()), this, SLOT(on_next_page_triggered()));
    connect(m_firstPageAction, SIGNAL(triggered()), this, SLOT(on_first_page_triggered()));
    connect(m_lastPageAction, SIGNAL(triggered()), this, SLOT(on_last_page_triggered()));



    // view action
    m_singlePageAction = new QAction(QIcon(":/icons/document-open.svg"),tr("&single page...", "Action: single page"), this);
    m_twoPageAction = new QAction(QIcon(":/icons/document-open.svg"),tr("&two page...", "Action: two page"), this);
    connect(m_singlePageAction, SIGNAL(triggered()), this, SLOT(on_single_page_triggered()));
    connect(m_twoPageAction, SIGNAL(triggered()), this, SLOT(on_two_page_triggered()));


}

void OfdMainWindow::createToolbar()
{
    m_fileToolbar = this->addToolBar(tr("filetoolbar"));
    m_fileToolbar->addActions(QList<QAction*>()
                              << m_fileOpenAction
                              << m_fileNewTabAction
                              );

    //edit toolbar
    m_editToolbar = this->addToolBar(tr("edittoolbar"));
    m_editToolbar->addActions(QList<QAction*>()
                              << m_firstPageAction
                              << m_previousPageAction
                              << m_nextPageAction
                              << m_lastPageAction
                              );



}

//弹出式 菜单
QMenu* OfdMainWindow::createPopupMenu()
{
    return NULL;
}

void OfdMainWindow::slotGoToPreviousPage()
{
    QMessageBox::information(NULL,"ss","dd");
}

void OfdMainWindow::slotGoToNextPage()
{
    QMessageBox::information(NULL,"ss","dd");
}
