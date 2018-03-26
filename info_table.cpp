#include "info_table.h"
#include "ui_info_table.h"
#include "user.h"
#include "shop.h"
#include <QDebug>
Info_Table::Info_Table(CCMIS* ccmis_system,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info_Table)
{
    mCCMIS = ccmis_system;
    ui->setupUi(this);
    int user_num = mCCMIS->GetUserNum();
    //设置按钮
//    BtnForSubsidy  =new QButtonGroup(this);
//    BtnForSubsidy->addButton(ui->radioButton,1);
//    ui->radioButton->setChecked(false);




    //设置关联
//    connect(ui->radioButton,SIGNAL(clicked()),this,
//                                   SLOT(onRadionClickedBtn()));


    CheckForSubsidy = ui->checkBox;
    CheckForSubsidy->setText("显示补助");
    if(user_num >= CCMIS::USER_TEA_EMP_BEGIN
            && user_num <= CCMIS::USER_TEA_EMP_END)
        CheckForSubsidy->setCheckable(true);
    else
        CheckForSubsidy->setCheckable(false);

    connect(CheckForSubsidy,SIGNAL(stateChanged(int)),SLOT(on_Check_Button_StateChoose(int)));


    GetWholeOneUserSearchTable( ui->tableWidget,user_num);
}

void Info_Table::on_Check_Button_StateChoose(int state)
{
    switch (state) {
    case Qt::Checked:
         GetWholeOneUserSubsidyTable(ui->tableWidget,mCCMIS->GetUserNum());
        break;
    case Qt::Unchecked:
        GetWholeOneUserSearchTable( ui->tableWidget,mCCMIS->GetUserNum());
        break;

    }
}






Info_Table::~Info_Table()
{
    delete ui;
}

void Info_Table::onRadionClickedBtn()
{
    int user_num = mCCMIS->GetUserNum();
    if(user_num >= CCMIS::USER_TEA_EMP_BEGIN
            && user_num <= CCMIS::USER_TEA_EMP_END)
        GetWholeOneUserSubsidyTable(ui->tableWidget,user_num);
    else
        qDebug()<<"不符合被补助条件";
    return;
}

//补助表格
void Info_Table::GetWholeOneUserSubsidyTable(QTableWidget* qtable,int inum)
{
    qtable->clear();
    //设置表头
    qtable->setColumnCount(5);
    qtable->setHorizontalHeaderLabels(
                QStringList()<<"日期" <<"时间" <<"入帐号"<<"被补助人"<<"金额");
    //设置列宽
    qtable->setColumnWidth(0,120);
    qtable->setColumnWidth(1,100);
    qtable->setColumnWidth(2,50);
    qtable->setColumnWidth(3,150);
    qtable->setColumnWidth(4,100);


    int RowCount = 0;

    Information* iter = mCCMIS->GetInfoPointer() ->next;

    while(iter!=NULL){
        if( (iter->Onumber == 2) && (iter->Inumber == inum))
            ShowSameOnumOneInfo(qtable,iter,RowCount);
        iter  = iter->next;

    }

    return;
}


void Info_Table::GetWholeOneUserSearchTable(QTableWidget* qtable,int onum)
{
     qtable->clear();
   //设置表头
   qtable->setColumnCount(5);
   qtable->setHorizontalHeaderLabels(
               QStringList()<<"日期" <<"时间" <<"入帐号"<<"商铺名"<<"金额");
   //设置列宽
   qtable->setColumnWidth(0,120);
   qtable->setColumnWidth(1,100);
   qtable->setColumnWidth(2,50);
   qtable->setColumnWidth(3,150);
   qtable->setColumnWidth(4,100);


   int RowCount = 0;

   Information* iter = mCCMIS->GetInfoPointer() ->next;

   while(iter!=NULL){
       if(iter->Onumber == onum)
           ShowSameOnumOneInfo(qtable,iter,RowCount);
       iter  = iter->next;

   }

   return;



}

void Info_Table::ShowSameOnumOneInfo(QTableWidget *qtable,Information* one_info,int& row_index)
{
   QString Name = mCCMIS->GetAllNameByNum(one_info->Inumber);
   QString Date = Information::InfoToDateStr(one_info);
   QString Time = Information::InfoToTimeStr(one_info);
   QString Money = Information::InfoToMoneyStr(one_info);
   qtable->insertRow(row_index);


   qtable->setItem(row_index,0,new QTableWidgetItem(Date));
   qtable->setItem(row_index,1,new QTableWidgetItem(Time));
   qtable->setItem(row_index,2,
                       new QTableWidgetItem(QString::number(one_info->Inumber)));

   qtable->setItem(row_index,3,new QTableWidgetItem(Name));
   qtable->setItem(row_index,4,new QTableWidgetItem(Money));
   row_index++;
}








 void Info_Table::GetWholeOneShopSearchTable(QTableWidget* qtable,int inum)
{
     qtable->clear();
    //设置表头
    qtable->setColumnCount(5);
    qtable->setHorizontalHeaderLabels(
                QStringList()<<"日期" <<"时间" <<"卡号"<<"姓名"<<"金额");
    //设置列宽
    qtable->setColumnWidth(0,120);
    qtable->setColumnWidth(1,100);
    qtable->setColumnWidth(2,50);
    qtable->setColumnWidth(3,100);
    qtable->setColumnWidth(4,100);


    int RowCount = 0;

    Information* iter = mCCMIS->GetInfoPointer() ->next;

    while(iter!=NULL){
        if(iter->Inumber == inum)
            ShowSameInumOneInfo(qtable,iter,RowCount);
        iter  = iter->next;

    }

    return;



}

void Info_Table::ShowSameInumOneInfo(QTableWidget *qtable,Information* one_info,int& row_index)
{
    QString UserName = mCCMIS->GetAllNameByNum(one_info->Onumber);
    QString Date = Information::InfoToDateStr(one_info);
    QString Time = Information::InfoToTimeStr(one_info);
    QString Money = Information::InfoToMoneyStr(one_info);
    qtable->insertRow(row_index);


    qtable->setItem(row_index,0,new QTableWidgetItem(Date));
    qtable->setItem(row_index,1,new QTableWidgetItem(Time));
    qtable->setItem(row_index,2,
                        new QTableWidgetItem(QString::number(one_info->Onumber)));

    qtable->setItem(row_index,3,new QTableWidgetItem(UserName));
    qtable->setItem(row_index,4,new QTableWidgetItem(Money));
    row_index++;
}

void Info_Table::on_radioButton_pressed()
{
    
}
