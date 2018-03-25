#ifndef INFO_TABLE_H
#define INFO_TABLE_H
#include <QTableWidgetItem>
#include <QWidget>
#include <QTableWidget>
#include "ccmis.h"
namespace Ui {
class Info_Table;
}

class Info_Table : public QWidget
{
    Q_OBJECT

public:
    explicit Info_Table(CCMIS* ccmis_system,QWidget *parent = 0);
    ~Info_Table();
    void PrintOneInfo(CCMIS* ccmis_system, Information* OneLineInfo,int  IndexOfRow);


    void ShowOneInfo(QTableWidget* shop_table,Information* one_info,int row_index);
    QTableWidget* GetWholeShopSearchTable();

private:
    Ui::Info_Table *ui;
    CCMIS* mCCMIS;
};

#endif // INFO_TABLE_H
