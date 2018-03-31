#ifndef SHOPSEARCHWINDOW_H
#define SHOPSEARCHWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <qtablewidget.h>

#include "ccmis.h"
#include "table_funcs.h"
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
    void time_dispose();
    void on_BackButton_clicked();

    void on_DeleteButton_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::ShopSearchWindow *ui;
    CCMIS *mCCMIS;
    Shop_Table* mShopTable;
};

#endif // SHOPSEARCHWINDOW_H
