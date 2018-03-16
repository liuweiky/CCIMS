#include <iostream>
#include "mainwindow.h"
#include <QApplication>

#include "ccmis.h"


int main(int argc, char *argv[])
{

    CCMIS c;

    //CCMIS::GenerateRandomMoney();

    QApplication a(argc, argv);
    MainWindow w;
   w.show();



    return a.exec();
}
