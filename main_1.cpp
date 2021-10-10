#include "mainwindow.h"
#include "exeloadview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    exeLoadView w;
    w.show();
    return a.exec();
}
