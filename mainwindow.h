#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include <QDesktopWidget>

#include "usermainwindow.h"
#include "placemainwindow.h"
#include "shopmainwindow.h"
#include "administratormainwindow.h"

#include "info_table.h"

#include "ccmis.h"

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    CCMIS* mCCMIS;
};

#endif // MAINWINDOW_H
