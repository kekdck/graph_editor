#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    
    return a.exec();
}
