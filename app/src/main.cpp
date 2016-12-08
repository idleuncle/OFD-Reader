#include <QApplication>
#include <ofdmainwindow.h>
#include <typedef.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OfdMainWindow w;
    //最大化显示
    w.setWindowState(Qt::WindowMaximized);
    w.show();

    return a.exec();
}
