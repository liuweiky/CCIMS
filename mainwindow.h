#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDialog>
#include <QMessageBox>

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
    void reshow();
    void on_pushButton_clicked();

signals:
    void BackMainWindow();
    void showname(QString);

private:
    Ui::MainWindow *ui;
    CCMIS* mCCMIS;
    ShopMainWindow *mSMW;
};

#endif // MAINWINDOW_H
