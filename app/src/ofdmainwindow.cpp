#include "ofdmainwindow.h"
#include <QVBoxLayout>
#include <QDockWidget>
#include <QToolButton>
#include <QPushButton>
#include <QFileDialog>
#include "documentview.h"
OfdMainWindow::OfdMainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_mainToolbar = NULL;
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
    throw "add tab";
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

void OfdMainWindow::createActions()
{

//    m_mainToolbar = this->addToolBar(tr("Tool Bar"));
//    m_fileOpenAction = new QAction(QIcon(":/icons/document-open.svg"),tr("&Open...", "Action: open file"), this);
//    m_fileOpenAction->setObjectName("file_open");

//    m_fileSaveCopyAction = new QAction(QIcon(":/icons/document-save.svg"),tr("&Open...", "Action: open file"), this);
//    m_fileSaveCopyAction->setObjectName("file_save");

//    connect(m_fileOpenAction, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
//    connect(m_fileSaveCopyAction, SIGNAL(triggered()), this, SLOT(slotSaveCopy()));


    // 上一页/下一页
    QWidget *navBar = new QWidget(m_mainToolbar);
    QHBoxLayout *navLayout = new QHBoxLayout;
    navBar->setLayout(navLayout);
    QToolButton *navPrevBtn = new QToolButton(navBar);
    navPrevBtn->setIcon(QIcon(":/icons/go-previous.svg"));
    navPrevBtn->setIconSize(QSize(40,40));
    connect(navPrevBtn,SIGNAL( clicked()), this, SLOT(slotGoToPreviousPage()));
    QToolButton *navNextBtn = new QToolButton(navBar);
    navNextBtn->setIcon(QIcon(":/icons/go-next.svg"));
    navNextBtn->setIconSize(QSize(40,40));
    connect(navNextBtn,SIGNAL( clicked()), this, SLOT(slotGoToNextPage()));

    navLayout->addWidget(navPrevBtn);
    navLayout->addWidget(navNextBtn);





    m_mainToolbar->addAction(m_fileOpenAction);
    m_mainToolbar->addAction(m_fileSaveCopyAction);
    m_mainToolbar->addWidget(navBar);



}


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
    this->createToolbar();
}

void OfdMainWindow::createToolbar()
{

    m_fileToolbar = this->addToolBar(tr("filetoolbar"));
    m_fileOpenAction = new QAction(QIcon(":/icons/document-open.svg"),tr("&Open...", "Action: open file"), this);
    m_fileOpenAction->setObjectName("file_open");

    m_fileToolbar->addAction(m_fileOpenAction);

    //edit toolbar
    m_editToolbar = this->addToolBar(tr("edittoolbar"));


    //view toolbar;

//    m_fileSaveCopyAction = new QAction(QIcon(":/icons/document-save.svg"),tr("&Open...", "Action: open file"), this);
//    m_fileSaveCopyAction->setObjectName("file_save");

//    connect(m_fileOpenAction, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
//    connect(m_fileSaveCopyAction, SIGNAL(triggered()), this, SLOT(slotSaveCopy()));


//    m_editToolbar->addAction(m_fileOpenAction);

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
