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

public slots:
    void showtime();
    void ShowNameSlot(QString);

private slots:
    //重新显示主界面：X，Y，宽，长
    void reshow(int,int,int,int);
    void on_BackButton_clicked();
    void on_SearchButton_clicked();
    void on_WorkButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    CCMIS* mCCMIS;
    Ui::ShopMainWindow *ui;
    ShopSearchWindow *mSSearchW;
    ShopServiceWindow *mSServiceW;
};

#endif // SHOPMAINWINDOW_H
