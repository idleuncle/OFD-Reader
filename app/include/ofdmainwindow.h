#ifndef OfdMainWindow_H
#define OfdMainWindow_H
#include <typedef.h>
#include <QMainWindow>
#include <QAction>
#include <QMessageBox>
#include <libofdengine.h>
#include <QToolBar>
#include <QTabWidget>
#include <QList>

class DocumentView;

class OfdMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit OfdMainWindow(QWidget *parent = 0);
    virtual ~OfdMainWindow();



    //=====标签页=====
    QTabWidget* m_tabWidget;

    int addTab(DocumentView* tab);

    void closeTab(DocumentView* tab);

    QList<DocumentView*> tabs() const;


    // init 初始化
    void init();

    void createToolbar();

    QScopedPointer<QToolBar*> m_mainToolbar1;

    //弹出式 菜单
    QMenu* createPopupMenu();



    //菜单
    QMenu *m_viewMenu;

    //工具栏
    QToolBar* m_mainToolbar;
    QToolBar* m_fileToolbar;
    QToolBar* m_editToolbar;
    QToolBar* m_viewToolbar;

    //pdf 显示模块
//    OfdView* m_ofdView;

    //菜单事件
    QAction* m_fileOpenAction;
    QAction *m_fileSaveCopyAction;



    //ofd file
    QString m_file;

    //Ofd Engine
//    libOfdEngine* m_OfdEngine;


    bool loadDocument(const QString &filename);

private:
    //初始化事件
    void createActions();

signals:

public slots:
    void slotOpenFile();
    void slotSaveCopy();

    void slotGoToPreviousPage();
    void slotGoToNextPage();

};

#endif // OfdMainWindow_H
