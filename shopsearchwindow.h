#ifndef SHOPSEARCHWINDOW_H
#define SHOPSEARCHWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTableWidget>

#include "ccims.h"
#include "aboutui.h"
#include "table_funcs.h"

namespace Ui {
class ShopSearchWindow;
}

class ShopSearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopSearchWindow(CCIMS *c, QWidget *parent = 0);
    ~ShopSearchWindow();
    QTableWidget* GetWholeShopSearchTable();
    void ShowOneInfo(QTableWidget* shop_table, Information* one_info,int row_index);

private slots:
    void time_dispose();
    void on_BackButton_clicked();


private:
    Ui::ShopSearchWindow *ui;
    CCIMS *mCCIMS;
    Shop_Table* mShopTable;
};

#endif // SHOPSEARCHWINDOW_H
