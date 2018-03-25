#include "info_table.h"
#include "ui_info_table.h"
#include "user.h"
#include "shop.h"

Info_Table::Info_Table(CCMIS* ccmis_system,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info_Table)
{
    mCCMIS = ccmis_system;
    ui->setupUi(this);
    QTableWidget* inum1104 ;
    inum1104 = GetWholeShopSearchTable();
    inum1104->show();
    ui->tableWidget = inum1104;
}

Info_Table::~Info_Table()
{
    delete ui;
}




QTableWidget* Info_Table::GetWholeShopSearchTable()
{
    QTableWidget* SSTable = new QTableWidget();
    //设置表头
    SSTable->setColumnCount(5);
    SSTable->setHorizontalHeaderLabels(
                QStringList()<<"日期" <<"时间" <<"卡号"<<"姓名"<<"金额");
    //设置列宽
    SSTable->setColumnWidth(0,120);
    SSTable->setColumnWidth(1,100);
    SSTable->setColumnWidth(2,50);
    SSTable->setColumnWidth(3,100);
    SSTable->setColumnWidth(4,100);


    int RowCount = SSTable->rowCount();

    Information* iter = mCCMIS->GetInfoPointer() ->next;
    while(iter!=NULL){
        if(iter->Inumber == 1104)
            ShowOneInfo(SSTable,iter,RowCount);
        iter  = iter->next;
        RowCount++;
    }

    return SSTable;



}

void Info_Table::ShowOneInfo(QTableWidget* shop_table,Information* one_info,int row_index)
{
    QString UserName = mCCMIS->GetAllNameByNum(one_info->Onumber);
    QString Date = Information::InfoToDateStr(one_info);
    QString Time = Information::InfoToTimeStr(one_info);
    QString Money = Information::InfoToMoneyStr(one_info);
    shop_table->insertRow(row_index);

    shop_table->setItem(row_index,0,new QTableWidgetItem(Date));
    shop_table->setItem(row_index,2,
                        new QTableWidgetItem(QString::number(one_info->Onumber)));

    shop_table->setItem(row_index,3,new QTableWidgetItem(UserName));
    shop_table->setItem(row_index,4,new QTableWidgetItem(Money));
}
