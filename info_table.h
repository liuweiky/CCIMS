#ifndef INFO_TABLE_H
#define INFO_TABLE_H

#include <QTableWidgetItem>
#include <QWidget>
#include <QTableWidget>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDateTimeEdit>
#include <QMessageBox>

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

    //只显示一个人的补助表格
    void GetWholeOneUserSubsidyTable(QTableWidget* qtable,int inum);

    //同一个入帐账号 表格
    void GetWholeOneUserSearchTable(QTableWidget* qtable,int onum);
    void ShowSameOnumOneInfo(QTableWidget *qtable,Information* one_info,int& row_index);



    //同一个出账账号 表格
    void ShowSameInumOneInfo(QTableWidget *qtable,Information* one_info, int &row_index);
    void GetWholeOneShopSearchTable(QTableWidget* qtable, int inum);


     //日期控件 设置
     void SetStartFinishRange(QDateEdit* start_edit,QDateEdit* finish_edit);


     void Table_Filtered_By_Date(QTableWidget* table,QDate* start_date ,
                                                     QDate* finish_date);
private:

     int mCurrentItem;

    Ui::Info_Table *ui;
    CCMIS* mCCMIS;

    QCheckBox* CheckForSubsidy;
    QDateEdit* Start_Date_Edit;
    QDateEdit* Finish_Date_Edit;

    QDate* Start_Date;
    QDate* Finish_Date;

public slots:

   void on_Check_Button_StateChoose(int state);

   void onStartDateChanged(const QDate &date);
   void onFinishDateChanged(const QDate &date);
private slots:
   void on_Search_clicked();
   
   void on_tableWidget_itemClicked(QTableWidgetItem *item);
   void on_DeleteButton_clicked();
   
//   void on_toExcelButton_clicked();
   void on_Reset_clicked();
};

#endif // INFO_TABLE_H
