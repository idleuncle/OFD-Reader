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
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>

namespace ofdreader
{
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

    void createMainMenu();

    void createToolbar();

    void craeteActions();


    // file action
    QAction* m_fileOpenAction;
    QAction* m_fileNewTabAction;
    QAction* m_RecentAction;
    QAction* m_closeWindowsAction;
    QAction* m_closeTabAction;
    QAction* m_saveAction;
    QAction* m_saveAsAction;
    QAction* m_showInFinderAction;


    // edit action
    QAction* m_previousPageAction;
    QAction* m_nextPageAction;
    QAction* m_firstPageAction;
    QAction* m_lastPageAction;

    //view action;
    QAction* m_singlePageAction;
    QAction* m_twoPageAction;




    // Dock
    QDockWidget* m_outlineDock;


    void createDockers();


    //弹出式 菜单
    QMenu* createPopupMenu();


    //菜单
    QMenu* m_editMenu;
    QMenu* m_fileMenu;
    QMenu* m_viewMenu;


    //工具栏
    QToolBar* m_fileToolbar;

    //用于编辑按钮工具栏
    QToolBar* m_editToolbar;

    //放大多小等工具栏
    QToolBar* m_viewToolbar;




    //菜单事件
    QAction *m_fileSaveCopyAction;



    //ofd file
    QString m_file;

    //Ofd Engine
    //    libOfdEngine* m_OfdEngine;


    bool loadDocument(const QString &filename);

    bool openInNewTab(const QString& filePath, int page = -1, const QRectF& highlight = QRectF(), bool quiet = false);
private:
    //初始化事件
    void createActions();

signals:

public slots:
    void slotOpenFile();
    void slotSaveCopy();

    void slotGoToPreviousPage();
    void slotGoToNextPage();

protected slots:
    // 打开文件
    void on_open_triggered();
    // 新标签打开文件
    void on_open_new_tab_triggered();
    // 前一页
    void on_previous_page_triggered();
    // 下一页
    void on_next_page_triggered();
    // 第一页
    void on_first_page_triggered();
    // 最后一页
    void on_last_page_triggered();
    // 单页显示模式
    void on_single_page_triggered();
    // 双页显示模式
    void on_two_page_triggered();
};

} // namespace ofdreader
#endif // OfdMainWindow_H
