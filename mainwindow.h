#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDialog>
#include <QMessageBox>
#include <QDesktopWidget>

#include "usermainwindow.h"
#include "placemainwindow.h"
#include "shopmainwindow.h"
#include "administratormainwindow.h"

#include "info_table.h"

#include "ccmis.h"
#include "aboutui.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void time_dispose();
    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;
    //这里我mac直接关出现一次提示，command+Q出现两次，目前不知为何

private:
    Ui::MainWindow *ui;
    CCMIS* mCCMIS;
};

#endif // MAINWINDOW_H
