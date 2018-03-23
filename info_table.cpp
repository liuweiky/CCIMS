#include "info_table.h"
#include "ui_info_table.h"
#include "user.h"
#include "shop.h"

Info_Table::Info_Table(CCMIS* ccmis_system,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info_Table)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(ccmis_system->GetTotalInfoNumber());
    QStringList Info_Header;
    Info_Header << " 日期 "<<"时间"<<"出账卡号"<<"出账用户名"<<"入账卡号"<<"入账用户名"<<"交易金额";

    ui->tableWidget->setHorizontalHeaderLabels(Info_Header);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,80);
    ui->tableWidget->setColumnWidth(5,170);
    ui->tableWidget->setColumnWidth(6,100);

    Information* iter =ccmis_system->GetInfoPointer()->next;
    int  row_index = 0;
    while(iter!=NULL){
        PrintOneInfo(ccmis_system,iter,row_index);
        iter = iter->next;
        row_index++;
    }

}

Info_Table::~Info_Table()
{
    delete ui;
}




void Info_Table::PrintOneInfo(CCMIS* ccmis_system,Information* OneLineInfo,int IndexOfRow)
{
    QString UserName,ShopName;
    UserName = ccmis_system->GetAllNameByNum(OneLineInfo->Onumber);
    ShopName = ccmis_system->GetAllNameByNum(OneLineInfo->Inumber);

    QString Date,Time,Money;
    QString year,month,day,hour,min,sec;
    year=QString::number(OneLineInfo->year);
    month =QString::number(OneLineInfo->month).sprintf("%02d",OneLineInfo->month);
    day =QString::number(OneLineInfo->day).sprintf("%02d",OneLineInfo->day);
    hour =QString::number(OneLineInfo->hour).sprintf("%02d",OneLineInfo->hour);
    min = QString::number(OneLineInfo->minute).sprintf("%02d",OneLineInfo->minute);
    sec = QString::number(OneLineInfo->second).sprintf("%02d",OneLineInfo->second);

    unsigned int MoneyInt,MoneyFloat;
    MoneyFloat = (OneLineInfo->money)%100;
    MoneyInt = (OneLineInfo->money - MoneyFloat)/100;

    Date = year + " - " + month + " - "+ day;
    Time = hour + ":" + min + ":" + sec;
    Money = QString::number(MoneyInt) + "." + QString::number(MoneyFloat);

    ui->tableWidget->setItem(IndexOfRow,0,new QTableWidgetItem(Date));
    ui->tableWidget->setItem(IndexOfRow,1,new QTableWidgetItem(Time));
    ui->tableWidget->setItem(IndexOfRow,2,new QTableWidgetItem(QString::number(OneLineInfo->Onumber)));
    ui->tableWidget->setItem(IndexOfRow,3,new QTableWidgetItem(UserName));
    ui->tableWidget->setItem(IndexOfRow,4,new QTableWidgetItem(QString::number(OneLineInfo->Inumber)));
    ui->tableWidget->setItem(IndexOfRow,5,new QTableWidgetItem(ShopName));
    ui->tableWidget->setItem(IndexOfRow,6,new QTableWidgetItem(Money));
}
