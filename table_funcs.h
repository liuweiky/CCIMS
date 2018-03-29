#ifndef TABLE_FUNCS_H
#define TABLE_FUNCS_H

//为了三个table window

#include<QTableWidget>
#include<QDateEdit>
#include<QCheckBox>
#include<QPushButton>
#include<QDate>
#include<QTableWidget>
#include<QDateTime>

#include"ccmis.h"

class Table_Parent
{
protected:
    //控件类成员
    QTableWidget* mTable;
    QDateEdit* mStart_Edit;
    QDateEdit* mFinish_Edit;
    QDate* mStart_Date;
    QDate* mFinish_Date;

    QPushButton* mFilter_Btn;
    QPushButton* mReset_Btn;
    QPushButton* mExport_Btn;

    CCMIS* mCCMIS;
//不清楚是否合适
     int mCurrent_Row_Index = 0;

public:
    Table_Parent(QTableWidget *table, QDateEdit* start_edit,
                 QDateEdit* finish_edit,QPushButton* filter_btn,
                 QPushButton* reset_btn, QPushButton* export_btn,
                 CCMIS* ccmis_sys);
    ~Table_Parent();

    void init_Date_Edit();
    void Table_Filtered_By_Date();
    void init_Subsidy_Header();
    void show_One_Info_Same_Num(Information*,int,int);
    void show_One_Info_All(Information*,int);
    //输出csv解决跨平台，得按照你自己的改
    void export_Table_To_CSV();


    //纯虚函数 子类给出实现 负责表格头
    virtual void init_Table_Header() = 0;

    void connectSignalsSlots();


//一些槽函数
protected slots:
    void on_Start_Date_Changed(const QDate &date);
    void on_Finish_Date_Changed(const QDate &date);
    void on_Filter_clicked();
    void on_Export_pressed();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_Reset_clicked();

};



class Admin_Table : public Table_Parent
{
private:
    QCheckBox* mSubsidy_Chk;
    //删 增 改
    QPushButton* mDelete_Btn;
    QPushButton* mInsert_Btn;
    QPushButton* mAlter_Btn;
public:
    Admin_Table(QTableWidget *table,QDateEdit* start_edit,
                QDateEdit* finish_edit,QPushButton* filter_btn,
                QPushButton* reset_btn,QPushButton* export_btn,
                CCMIS* ccmis_sys,QPushButton* delete_btn,
                QPushButton* insert_btn,QPushButton* alter_btn,
                QCheckBox* subsidy_check);
    void init_Table_Header();
};


class Shop_Table: public Table_Parent
{
private:
      Shop* mCurrent_Shop;

     //删 增 改 只能修改自己店铺相关的
     QPushButton* mDelete_Btn;
     QPushButton* mInsert_Btn;
     QPushButton* mAlter_Btn;

public:
    Shop_Table(QTableWidget *table, QDateEdit* start_edit,
               QDateEdit* finish_edit,QPushButton* filter_btn,
               QPushButton* reset_btn, QPushButton* export_btn,
               CCMIS* ccmis_sys,QPushButton* delete_btn,
               QPushButton* insert_btn,QPushButton* alter_btn);
    void init_Table_Header();
};




class User_Table: public Table_Parent
{
private:
    QCheckBox* mSubsidy_Chk;
    User* mCurrent_User;
public:
    User_Table(QTableWidget *table, QDateEdit* start_edit,
               QDateEdit* finish_edit,QPushButton* filter_btn,
               QPushButton* reset_btn, QPushButton* export_btn,
               CCMIS* ccmis_sys,QCheckBox* subsidy_check);
    void init_Table_Header();
    void init_Subsidy_Header();
};
























#endif // TABLE_FUNCS_H
