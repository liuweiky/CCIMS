#include <iostream>
#include "mainwindow.h"
#include <QApplication>

#include <fileutil.h>


int main(int argc, char *argv[])
{
    FileUtil::writeLine("ccc");
    string s = "123456789";
    s += "\n";
    s += "987654321";
    FileUtil::writeSerialNumbers(s);

    cout<<FileUtil::readSerialNumbers();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
