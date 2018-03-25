#include "shopsearchwindow.h"
#include "ui_shopsearchwindow.h"
#include "information.h"
ShopSearchWindow::ShopSearchWindow(CCMIS* ccmis_sys,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopSearchWindow)
{
    ui->setupUi(this);
    mCCMIS = ccmis_sys;

    //表格显示
    ui->tableWidget = GetWholeShopSearchTable();
    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);
    //名字显示

}

ShopSearchWindow::~ShopSearchWindow()
{
    delete ui;
}


QTableWidget* ShopSearchWindow::GetWholeShopSearchTable()
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
        if(iter->Inumber == mCCMIS->GetUserNum())
            ShowOneInfo(SSTable,iter,RowCount);
        iter  = iter->next;
        RowCount++;
    }

    return SSTable;



}

void ShopSearchWindow::ShowOneInfo(QTableWidget* shop_table,Information* one_info,int row_index)
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

void ShopSearchWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopSearchWindow::ShowNameSlot(QString txtname)
{

    int thisShopNum = mCCMIS->GetUserNum();
    ui->UserName->setText(mCCMIS->GetAllNameByNum(thisShopNum));
}

void ShopSearchWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}
