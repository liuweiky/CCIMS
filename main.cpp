#include <iostream>

#include <QApplication>

#include "ccmis.h"

#include "mainwindow.h"
#include "shopmainwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    ShopMainWindow w;
    w.show();


    return a.exec();
}
