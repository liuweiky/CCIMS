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
    explicit ShopSearchWindow(CCMIS *c, QWidget *parent = 0);
    ~ShopSearchWindow();
    QTableWidget* GetWholeShopSearchTable();
    void ShowOneInfo(QTableWidget* shop_table, Information* one_info,int row_index);

private slots:
    void showtime();
    void on_BackButton_clicked();

private:
    Ui::ShopSearchWindow *ui;
    CCMIS *mCCMIS;
};

#endif // SHOPSEARCHWINDOW_H
