#ifndef SHOPMAINWINDOW_H
#define SHOPMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "shopsearchwindow.h"
#include "shopservicewindow.h"

#include "ccims.h"
#include "aboutui.h"

namespace Ui {
class ShopMainWindow;
}

class ShopMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopMainWindow(CCIMS* c, QWidget *parent = 0);
    ~ShopMainWindow();

private slots:
    void time_dispose();
    void on_BackButton_clicked();
    void on_SearchButton_clicked();
    void on_WorkButton_clicked();

private:
    CCIMS* mCCIMS;
    Ui::ShopMainWindow *ui;
};

#endif // SHOPMAINWINDOW_H
