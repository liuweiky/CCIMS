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

    Start_Date = new QDate();
    Finish_Date = new QDate();

    CheckForSubsidy = ui->checkBox;
    CheckForSubsidy->setText("显示补助");
    if(user_num >= CCMIS::USER_TEA_EMP_BEGIN
            && user_num <= CCMIS::USER_TEA_EMP_END)
        CheckForSubsidy->setCheckable(true);
    else
        CheckForSubsidy->setCheckable(false);

    connect(CheckForSubsidy,SIGNAL(stateChanged(int)),SLOT(on_Check_Button_StateChoose(int)));



    //日期筛选
    //Start_Date_Edit = new QDateEdit(this);
    //Finish_Date_Edit = new QDateEdit(this);
    Start_Date_Edit = ui->start;
    Finish_Date_Edit = ui->finish;
    SetStartFinishRange(Start_Date_Edit,Finish_Date_Edit);
    connect(Start_Date_Edit,SIGNAL(dateChanged(QDate)),
            SLOT(onStartDateChanged(QDate)));
    connect(Finish_Date_Edit,SIGNAL(dateChanged(QDate)),
            SLOT(onFinishDateChanged(QDate)));




    GetWholeOneUserSearchTable( ui->tableWidget,user_num);
    Table_Filtered_By_Date(ui->tableWidget, new QDate(2018,2,10), new QDate(2018,2,15));
}




void Info_Table::SetStartFinishRange(QDateEdit* start_edit,QDateEdit* finish_edit)
{
    QDate start_date(2018,1,1);



    //起始时间范围限制
    start_edit->setDate(start_date);
    start_edit->setMaximumDate(QDate::currentDate());
    start_edit->setMinimumDate(start_date);

    //结束时间范围限制
    finish_edit->setDate(QDate::currentDate());
    finish_edit->setMaximumDate(QDate::currentDate());
    finish_edit->setMinimumDate(start_date);


    //弹出框
    start_edit->setCalendarPopup(true);
    finish_edit->setCalendarPopup(true);  // 日历弹出
}

void Info_Table::onStartDateChanged(const QDate &date)
{
   qDebug() << "StartDateTime : " << date;
    this->Start_Date->setDate(date.year(),date.month(),date.day());

    this->Finish_Date_Edit->setMinimumDate(date);
}

void Info_Table::onFinishDateChanged(const QDate &date)
{
    qDebug() << "FinishDateTime : " << date;
    this->Finish_Date->setDate(date.year(),date.month(),date.day());
    qDebug() << "FinishDateTime : " << date;
    this->Start_Date_Edit->setMaximumDate(date);
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
   QDateTime info_date_time = Information::InfoToDateTime(one_info);

   QString Date = info_date_time.toString("yyyy-MM-dd");


   QString Time = info_date_time.toString("hh:mm:ss");
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


void Info_Table::on_Search_clicked()
{

}

void Info_Table::Table_Filtered_By_Date(QTableWidget* table,QDate* start_date,QDate* finish_date)
{

    for( int i = 0; i < table->rowCount(); ++i )
    {
        bool match = false;
        QTableWidgetItem *item = table->item( i, 0 );
        QDate one_date = QDate::fromString (item->text(),"yyyy-MM-dd" );
        //qDebug()<<one_date;
        if( (one_date >= (*start_date)) && (one_date <(*finish_date)))

        { qDebug()<<one_date;
            match = true;
           // break;
        }
        table->setRowHidden( i, !match );
     }

}



