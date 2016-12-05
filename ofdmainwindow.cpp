#include "ofdmainwindow.h"
#include <QVBoxLayout>
#include <QDockWidget>
#include <QToolButton>
#include <QPushButton>
#include <QFileDialog>
OfdMainWindow::OfdMainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget(this);
    m_OfdEngine = new libOfdEngine();
    m_OfdEngine->loadtest();

    m_ofdView = new OfdView(m_OfdEngine,this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_ofdView);



    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    m_ofdView->setofdengine(m_OfdEngine);


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
    if(m_mainToolbar)
    {
        delete m_mainToolbar;
        m_mainToolbar = NULL;
    }

}



void OfdMainWindow::createActions()
{

    m_mainToolbar = this->addToolBar(tr("Tool Bar"));
    m_fileOpenAction = new QAction(QIcon(":/icons/document-open.png"),tr("&Open...", "Action: open file"), this);
    m_fileOpenAction->setObjectName("file_open");

    m_fileSaveCopyAction = new QAction(QIcon(":/icons/document-save.png"),tr("&Open...", "Action: open file"), this);
    m_fileSaveCopyAction->setObjectName("file_open");

    connect(m_fileOpenAction, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
    connect(m_fileSaveCopyAction, SIGNAL(triggered()), this, SLOT(slotSaveCopy()));


    // 上一页/下一页
    QWidget *navBar = new QWidget(m_mainToolbar);
    QHBoxLayout *navLayout = new QHBoxLayout;
    navBar->setLayout(navLayout);
    QToolButton *navPrevBtn = new QToolButton(navBar);
    navPrevBtn->setIcon(QIcon(":/icons/go-previous.png"));
    connect(navPrevBtn,SIGNAL( clicked()), this, SLOT(slotGoToPreviousPage()));
    QToolButton *navNextBtn = new QToolButton(navBar);
    navNextBtn->setIcon(QIcon(":/icons/go-next.png"));
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
        m_ofdView->test_cairo();
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
    return m_OfdEngine->load(filename);
}

void OfdMainWindow::slotSaveCopy()
{
    QMessageBox::information(this,tr("hmmmm"),tr("save file"));
}


void OfdMainWindow::slotGoToPreviousPage()
{
    QMessageBox::information(NULL,"ss","dd");
}

void OfdMainWindow::slotGoToNextPage()
{
    QMessageBox::information(NULL,"ss","dd");
}
