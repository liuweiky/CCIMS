#ifndef SHOPSEARCHWINDOW_H
#define SHOPSEARCHWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>
#include "ccmis.h"
#include <qtablewidget.h>
namespace Ui {
class ShopSearchWindow;
}

class ShopSearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopSearchWindow(CCMIS* ccmis_sys,QWidget *parent = 0);
    ~ShopSearchWindow();
    QTableWidget* GetWholeShopSearchTable();
    void ShowOneInfo(QTableWidget* shop_table, Information* one_info,int row_index);

public slots:
    void showtime();
    void ShowNameSlot(QString);

private slots:
    void on_BackButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::ShopSearchWindow *ui;
    CCMIS *mCCMIS;
};

#endif // SHOPSEARCHWINDOW_H
