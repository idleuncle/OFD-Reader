#ifndef OfdMainWindow_H
#define OfdMainWindow_H

#include <QMainWindow>
#include <ofdview.h>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
class OfdMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit OfdMainWindow(QWidget *parent = 0);
    virtual ~OfdMainWindow();

    //菜单
    QMenu *m_viewMenu;

    //工具栏
    QToolBar* m_mainToolbar;


    //pdf 显示模块
    OfdView* m_ofdView;


    //菜单事件
    QAction* m_fileOpenAction;
    QAction *m_fileSaveCopyAction;


private:
    //初始化事件
    void createActions();

signals:

public slots:
    void slotOpenFile();
    void slotSaveCopy();
};

#endif // OfdMainWindow_H
