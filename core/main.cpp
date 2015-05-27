#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //bool exists = QFile::exists("/home/bk/Desktop/Zigzan.wav");
    out();
    w.show();

 //   qDebug () << exists  << endl;

    return a.exec();
}
