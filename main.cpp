#include <iostream>
#include "mainwindow.h"
#include "usermainwindow.h"
#include <QApplication>

#include "ccmis.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    usermainwindow w;
    w.show();


    return a.exec();
}
