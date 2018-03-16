#include <iostream>
#include "mainwindow.h"
#include <QApplication>

#include "ccmis.h"


int main(int argc, char *argv[])
{

    CCMIS c;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
