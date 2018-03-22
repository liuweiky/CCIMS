#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDialog>
#include <QMessageBox>
#include <QDesktopWidget>

#include "ccmis.h"

#include "shopmainwindow.h"
#include "info_table.h"
#include "usermainwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //重新显示主界面：X，Y，宽，长
    void reshow(int,int,int,int);
    void on_pushButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::MainWindow *ui;
    CCMIS* mCCMIS;
    ShopMainWindow *mSMW;
};

#endif // MAINWINDOW_H
