#ifndef SHOPMAINWINDOW_H
#define SHOPMAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

#include "shopsearchwindow.h"
#include "shopservicewindow.h"

#include "ccmis.h"

namespace Ui {
class ShopMainWindow;
}

class ShopMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopMainWindow(CCMIS* c, QWidget *parent = 0);
    ~ShopMainWindow();

private slots:
    void showtime();
    void on_BackButton_clicked();
    void on_SearchButton_clicked();
    void on_WorkButton_clicked();

private:
    CCMIS* mCCMIS;
    Ui::ShopMainWindow *ui;
};

#endif // SHOPMAINWINDOW_H
