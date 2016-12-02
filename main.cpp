#include <QApplication>
#include <ofdmainwindow.h>
#include <typedef.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    OfdMainWindow w;
    //最大化显示
//    w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
//    w.showMaximized();
    w.setWindowState(Qt::WindowMaximized);
    w.show();

    return a.exec();
}
