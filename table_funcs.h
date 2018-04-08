#ifndef TABLE_FUNCS_H
#define TABLE_FUNCS_H

#include <QTableWidget>
#include <QDateEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDateTime>
#include <QObject>
#include <QHeaderView>
#include <QApplication>
#include <QLabel>

#include "ccims.h"
#include "struct_funcs.h"

class Table_Parent: public QWidget
{
    Q_OBJECT
public:
    //TODO: Need parent pointer……
    //控件类成员
    QTableWidget* mTable;
    QDateEdit* mStart_Edit;
    QDateEdit* mFinish_Edit;
    QDate* mStart_Date;
    QDate* mFinish_Date;

    QPushButton* mFilter_Btn;
    QPushButton* mReset_Btn;
    QPushButton* mExport_Btn;

    CCIMS* mCCIMS;
    //不清楚是否合适?
    int mCurrentItemIndex = -1;

    Table_Parent(QTableWidget *table, QDateEdit* start_edit,
                 QDateEdit* finish_edit,QPushButton* filter_btn,
                 QPushButton* reset_btn, QPushButton* export_btn,
                 CCIMS* CCIMS_sys);

    void init_Date_Edit();
    void Table_Filtered_By_Date(QTableWidget *qtable = NULL);
    void init_Subsidy_Header();
    void show_One_Info_Same_Num(Information*,int,int);
    void show_One_Info_All(Information*,int);
    void export_Table_To_CSV();
    QString get_Info_Tag_By_RowIndex(int row_index);
    QString get_Current_Table_Money();

    //纯虚函数 子类给出实现 负责表格头
    virtual void init_Table_Header() = 0 ;
    virtual void DelItem() = 0;

public slots:
    void on_Start_Date_Changed(const QDate &date);
    void on_Finish_Date_Changed(const QDate &date);
    void on_Filter_clicked();
    void on_Export_pressed();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_Reset_clicked();
    void on_DeleteButton_clicked();
};

class Admin_Table : public Table_Parent
{
    Q_OBJECT
public:
    //删 增 改
    QPushButton* mDelete_Btn;
    QPushButton* mInsert_Btn;
    QPushButton* mAlter_Btn;
    QCheckBox* mSubsidy_Chck;

    Admin_Table(QTableWidget *table, QDateEdit* start_edit,
    QDateEdit* finish_edit,QPushButton* filter_btn,
    QPushButton* reset_btn, QPushButton* export_btn,
    CCIMS* CCIMS_sys,QPushButton* delete_btn,
    QPushButton *insert_btn, QPushButton *alter_btn,
    QCheckBox *subsidy_check);
    void init_Table_Header();
    void DelItem();
    void init_Super_Table_Header(int now_num);
public slots:
    void on_Subsidy_Check_Admin(int);
    void on_Reset_clicked();
};


class Shop_Table: public Table_Parent
{
    Q_OBJECT
public:
    Shop* mCurrent_Shop;
    QLabel* mTotal_Profit;
    Shop_Table(QTableWidget *table, QDateEdit* start_edit,
               QDateEdit* finish_edit,QPushButton* filter_btn,
               QPushButton* reset_btn, QPushButton* export_btn,
               CCIMS* CCIMS_sys,QLabel* total_label);
    void init_Table_Header();
    void DelItem(){}
public slots:
    void on_Filter_clicked_Shop();
    void on_Reset_clicked_Shop();
};

class ShopPlace_Table: public Table_Parent
{
    Q_OBJECT
public:
    Shop* mCurrent_ShopPalace;
    QLabel* mTotal_Profit;
    ShopPlace_Table(QTableWidget *table, QDateEdit* start_edit,
               QDateEdit* finish_edit,QPushButton* filter_btn,
               QPushButton* reset_btn, QPushButton* export_btn,
               CCIMS* CCIMS_sys,QLabel* total_label);
    void init_Table_Header();
    void DelItem(){}
public slots:
    void on_Filter_clicked_SP();
    void on_Reset_clicked_SP();
};

class User_Table: public Table_Parent
{
    Q_OBJECT
public:
    User* mCurrent_User;
    QCheckBox* mSubsidy_Chck;
    User_Table(QTableWidget *table, QDateEdit* start_edit,
               QDateEdit* finish_edit,QPushButton* filter_btn,
               QPushButton* reset_btn, QPushButton* export_btn,
               CCIMS* CCIMS_sys,QCheckBox* subsidy_check);
    void init_Table_Header();
    void init_Subsidy_Header();
    void DelItem(){}

public slots:
    void on_Subsidy_Check_User(int);
    void on_Reset_clicked();
};

#endif // TABLE_FUNCS_H
