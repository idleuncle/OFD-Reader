#include "ofdmainwindow.h"
#include <QVBoxLayout>
#include <QDockWidget>
OfdMainWindow::OfdMainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget(this);
    m_ofdView = new OfdView(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_ofdView);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);


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

    m_mainToolbar->addAction(m_fileOpenAction);
    m_mainToolbar->addAction(m_fileSaveCopyAction);



}


void OfdMainWindow::slotOpenFile()
{
     QMessageBox::information(this, tr("Hmmm..."), tr("openfile"));

}

void OfdMainWindow::slotSaveCopy()
{
    QMessageBox::information(this,tr("hmmmm"),tr("save file"));
}
