#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "superusermainwindow.h"
#include "ccmis.h"
#include "info_table.h"
#include <QDialog>
#include <QMessageBox>

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
