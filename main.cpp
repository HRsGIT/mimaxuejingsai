#include "mainwindow.h"
#include "exeloadview.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    exeLoadView w;
    qDebug("123");
    w.show();
    return a.exec();
}
