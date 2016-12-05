#ifndef OfdMainWindow_H
#define OfdMainWindow_H
#include <typedef.h>
#include <QMainWindow>
#include <ofdview.h>
#include <QAction>
#include <QMessageBox>
#include <libofdengine.h>
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


    libOfdEngine* m_OfdEngine;

    //ofd file
    QString m_file;

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
