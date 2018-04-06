#include "table_funcs.h"

//-----------------------------------------------------------
//----------------------------------------------------父类函数
Table_Parent::Table_Parent
               (QTableWidget *table, QDateEdit* start_edit,
               QDateEdit* finish_edit,QPushButton* filter_btn,
               QPushButton* reset_btn, QPushButton* export_btn,
               CCMIS* ccmis_sys):QWidget(NULL)
{
    mTable = table;
    mStart_Edit = start_edit;
    mFinish_Edit = finish_edit;
    mFilter_Btn = filter_btn;
    mReset_Btn = reset_btn;
    mExport_Btn = export_btn;
    mCCMIS = ccmis_sys;
    init_Date_Edit();

    mCurrentItemIndex = -1;
}

void Table_Parent::init_Date_Edit()
{
    QDate start_date(2018,1,1);
    mStart_Date = new QDate(start_date);
    mFinish_Date = new QDate(QDate::currentDate());

    //起始时间范围限制
    mStart_Edit->setDate(start_date);
    mStart_Edit->setMaximumDate(QDate::currentDate());
    mStart_Edit->setMinimumDate(start_date);

    //结束时间范围限制
    mFinish_Edit->setDate(QDate::currentDate());
    mFinish_Edit->setMaximumDate(QDate::currentDate());
    mFinish_Edit->setMinimumDate(start_date);

    //弹出日历选择框
    mStart_Edit->setCalendarPopup(true);
    mFinish_Edit->setCalendarPopup(true);
}

void Table_Parent::Table_Filtered_By_Date(QTableWidget *qtable)
{
    if(qtable == NULL)
        qtable = mTable;

    for( int i = 0; i < qtable->rowCount(); ++i )
    {
        bool match = false;
        QTableWidgetItem *item = qtable->item( i, 0 );
        QDate one_date = QDate::fromString (item->text(),"yyyy-MM-dd" );
        if( (one_date >= (*mStart_Date)) && (one_date <= (*mFinish_Date))){
            match = true;
        }
        qtable->setRowHidden( i, !match );
     }
}

//父类的补助查看，可以查看全部的补助信息
void Table_Parent::init_Subsidy_Header()
{

    mTable->setColumnCount(6);
    mTable->setHorizontalHeaderLabels(
           QStringList()<<"日期" <<"时间" <<"入帐号"<<"被补助人"<<"金额"<<"流水号");
    mTable->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    int RowCount = 0;
    Information* iter = mCCMIS->GetInfoPointer() ->next;
    while(iter!=NULL){
        if(iter->Onumber == 2)
            show_One_Info_Same_Num(iter,RowCount,iter->Inumber);
        iter = iter->next;
    }
    RowCount = 0;
    return;
}

void Table_Parent::show_One_Info_Same_Num
(Information* one_info,int row_index,int inum_or_onum)
{
    mTable->insertRow(row_index);
    QString Name = mCCMIS->GetAllNameByNum(inum_or_onum);
    QDateTime info_date_time = Information::InfoToDateTime(one_info);
    QString Date = info_date_time.toString("yyyy-MM-dd");
    QString Time = info_date_time.toString("hh:mm:ss");
    QString Money = Information::InfoToMoneyStr(one_info);
    QString NumStr = QString::number(inum_or_onum).sprintf("%04d",inum_or_onum);
    QString tag = QString::fromLocal8Bit(one_info->tag.data());

    mTable->setItem(row_index,0,new QTableWidgetItem(Date));
    mTable->setItem(row_index,1,new QTableWidgetItem(Time));
    mTable->setItem(row_index,2,new QTableWidgetItem(NumStr));
    mTable->setItem(row_index,3,new QTableWidgetItem(Name));
    mTable->setItem(row_index,4,new QTableWidgetItem(Money));
    mTable->setItem(row_index,5,new QTableWidgetItem(tag));
}

void Table_Parent::show_One_Info_All(Information *one_info, int row_index)
{
    //每个项目转成QString
    QString InName  = mCCMIS->GetAllNameByNum(one_info->Inumber);
    QString OutName = mCCMIS->GetAllNameByNum(one_info->Onumber);
    QString InNumStr = QString::number(one_info->Inumber).sprintf("%04d",one_info->Inumber);
    QString OutNumStr = QString::number(one_info->Onumber).sprintf("%04d",one_info->Onumber);
    QDateTime info_date_time = Information::InfoToDateTime(one_info);
    QString Date = info_date_time.toString("yyyy-MM-dd");
    QString Time = info_date_time.toString("hh:mm:ss");
    QString Money = Information::InfoToMoneyStr(one_info);
    QString tag = QString::fromLocal8Bit(one_info->tag.data());
    //插入一行
    mTable->insertRow(row_index);

   // 参见顺序<<"日期" <<"时间" <<"出账号"<<"出账账户"<<"入账号"<<"入账账户"<<"金额"
    mTable->setItem(row_index,0,new QTableWidgetItem(Date));
    mTable->setItem(row_index,1,new QTableWidgetItem(Time));
    mTable->setItem(row_index,2,new QTableWidgetItem(OutNumStr));
    mTable->setItem(row_index,3,new QTableWidgetItem(OutName));
    mTable->setItem(row_index,4,new QTableWidgetItem(InNumStr));
    mTable->setItem(row_index,5,new QTableWidgetItem(InName));
    mTable->setItem(row_index,6,new QTableWidgetItem(Money));
    mTable->setItem(row_index,7,new QTableWidgetItem(tag));
}

void Table_Parent::export_Table_To_CSV(){
    //打开.csv文件
    QFile file("table.csv");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Output file failed!";
        return;
    }
    QTextStream out(&file);
    QString str;
    //获取表格内容
    int row = mTable->rowCount();//表格总行数
    int col = mTable->columnCount();
    for(int i = 0; i < row; i ++) {
        for(int j = 0; j < col; j++) {
            str = mTable->item(i, j)->text();
            if (j == col - 1 || j == 0) {   //转文本
                out << str << "\t" << ",";  //强制转文本，防止科学记数法
            }else{
                out << str << ",";  // 写入文件
            }
        }
        out << "\n";
    }
    file.close();
}

QString Table_Parent::get_Info_Tag_By_RowIndex(int row_index)
{
    if(row_index!=-1) {
        QVector<QString> whole_line;
        for(int i = 0; i < mTable->columnCount(); i++) {
            //遍历第row行的所有信息
            QString index = mTable->item(row_index,i)->text();
            whole_line.append(index);
        }

        QDate date = QDate::fromString(whole_line[0],"yyyy-MM-dd");
        QString tag_date = date.toString("yyyyMMdd");
        QTime time = QTime::fromString(whole_line[1],"hh:mm:ss");
        QString tag_time = time.toString("hhmmss");
        QString tag_onum,tag_inum,tag_money;

        return (tag_date+tag_time+tag_onum+tag_inum+tag_money);
    }else{
        return QString("");
    }
}



QString Table_Parent::get_Current_Table_Money()
{
    int col_index = 0;
    int cur_num =this->mCCMIS->GetUserNum();
    col_index =(cur_num%100 == 0)? 6:4;
    double total=0;
    qDebug()<<this->mTable->rowCount();
    for(int i = 0;i<this->mTable->rowCount();i++)
    {
        if(this->mTable->isRowHidden(i))
            continue;
        QString cur_money = this->mTable->item(i,col_index)->text();
        double cur_money_d = std::stod(cur_money.toStdString());
        total += cur_money_d;

    }
    return QString::number(total).sprintf("%.2f",total);
}




//----------------------------------------------------------父类槽函数
void Table_Parent::on_Start_Date_Changed(const QDate &date)
{
    this->mStart_Date->setDate(date.year(),date.month(),date.day());
    this->mFinish_Edit->setMinimumDate(date);
}

void Table_Parent::on_Finish_Date_Changed(const QDate &date)
{
    this->mFinish_Date->setDate(date.year(),date.month(),date.day());
    this->mStart_Edit->setMaximumDate(date);
}


void Table_Parent::on_Filter_clicked()
{
    this->Table_Filtered_By_Date(mTable);
}

void Table_Parent::on_Export_pressed()
{
    this->export_Table_To_CSV();
    QApplication::setQuitOnLastWindowClosed(false);
    QMessageBox::information(NULL, tr("提示"),
                            tr("导出成功！"),
                             QMessageBox::Yes);
}

void Table_Parent::on_Reset_clicked()
{
    this->mTable->setRowCount(0);
    this->mTable->clear();
    this->init_Table_Header();
}

void Table_Parent::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    mCurrentItemIndex = item->row();
    qDebug()<<get_Info_Tag_By_RowIndex(mCurrentItemIndex);
}

void Table_Parent::on_DeleteButton_clicked()
{
    this->DelItem();
}

//-----------------------------------------------------------
//-----------------------------------------------Admin 子类函数
Admin_Table::Admin_Table
            (QTableWidget *table, QDateEdit* start_edit,
             QDateEdit* finish_edit,QPushButton* filter_btn,
             QPushButton* reset_btn, QPushButton* export_btn,
             CCMIS* ccmis_sys,QPushButton* delete_btn,
             QPushButton *insert_btn, QPushButton *alter_btn,
             QCheckBox *subsidy_check)
        :Table_Parent(table, start_edit,finish_edit,filter_btn,
                    reset_btn, export_btn,ccmis_sys)
{
    mSubsidy_Chck = subsidy_check;
    mDelete_Btn = delete_btn;
    mInsert_Btn = insert_btn;
    mAlter_Btn  = alter_btn;
    init_Table_Header();
}

void Admin_Table::init_Table_Header()
{

    mTable->setColumnCount(8);
    mTable->setHorizontalHeaderLabels(
          QStringList()<<"日期" <<"时间" <<"出账号"<<"出账账户"
                       <<"入账号"<<"入账账户"<<"金额"<<"流水号");
    mTable->horizontalHeader()->setStretchLastSection(true);    //就是这个地方

    int RowCount = 0;
    Information* iter = mCCMIS->GetInfoPointer() ->next;
    while(iter!=NULL){
       show_One_Info_All(iter,RowCount);
       iter  = iter->next;
    }
    RowCount = 0;
    return;
}

void Admin_Table::DelItem()
{
    if (mCurrentItemIndex != -1) {
        Information* info = mCCMIS->GetInfoByTag
                (mTable->item(mCurrentItemIndex,7)->text());

        mCCMIS->NewRefund(info);
        mTable->removeRow(mCurrentItemIndex);
        mCurrentItemIndex = -1;
    }
}

//--------------------------------------------------admin槽函数
void Admin_Table::on_Subsidy_Check_Admin(int state)
{
    switch (state) {
    case Qt::Checked:
        this->mTable->setRowCount(0);
        init_Subsidy_Header();
        break;
    case Qt::Unchecked:
        this->mTable->setRowCount(0);
        init_Table_Header();
        break;
    }
}

void Admin_Table::on_Reset_clicked()
{
    if(mSubsidy_Chck->isChecked()){
        this->mTable->setRowCount(0);
        init_Subsidy_Header();
    }else{
        this->mTable->setRowCount(0);
        init_Table_Header();
    }
}

//-------------------------------------------------------------------
//---------------------------------------------------------Shop类子函数
Shop_Table::Shop_Table(QTableWidget *table, QDateEdit* start_edit,
                       QDateEdit* finish_edit, QPushButton* filter_btn,
                       QPushButton* reset_btn, QPushButton* export_btn,
                       CCMIS* ccmis_sys, QLabel *total_label)
        :Table_Parent(table, start_edit,finish_edit,filter_btn,
                    reset_btn, export_btn,ccmis_sys)
{
    mCurrent_Shop = mCCMIS->GetCurrentShop();
    mTotal_Profit = total_label;



    init_Table_Header();
    mTotal_Profit->setText("总盈利：" + get_Current_Table_Money() + " 元");
}

void Shop_Table::init_Table_Header()
{
    mTable->setColumnCount(6);
    mTable->setHorizontalHeaderLabels(
          QStringList()<<"日期" <<"时间" <<"出账号"<<"出账账户"<<"金额"<<"流水号");
    mTable->horizontalHeader()->setStretchLastSection(true); //就是这个地方

    int RowCount = 0;
    Information* iter = mCCMIS->GetInfoPointer() ->next;
    while(iter!=NULL){
        if ((int)iter->Inumber == mCurrent_Shop->number) {
            show_One_Info_Same_Num(iter,RowCount,iter->Onumber);
        }
        iter  = iter->next;
    }
}



void Shop_Table::on_Filter_clicked_Shop()
{
    this->Table_Filtered_By_Date(mTable);
    this->mTotal_Profit->setText("总盈利：" + get_Current_Table_Money() + " 元");
}


void Shop_Table::on_Reset_clicked_Shop()
{
    this->mTable->setRowCount(0);
    this->mTable->clear();
    this->init_Table_Header();
    this->mTotal_Profit->setText("总盈利：" + get_Current_Table_Money() + " 元");
}



//---------------------------------------------------------------------
//-----------------------------------------------------------大商铺类子函数
ShopPlace_Table::ShopPlace_Table(QTableWidget *table, QDateEdit* start_edit,
                       QDateEdit* finish_edit, QPushButton* filter_btn,
                       QPushButton* reset_btn, QPushButton* export_btn,
                       CCMIS* ccmis_sys, QLabel *total_label)
        :Table_Parent(table, start_edit,finish_edit,filter_btn,
                    reset_btn, export_btn,ccmis_sys)
{
    mCurrent_ShopPalace = mCCMIS->GetCurrentShop();
    mTotal_Profit = total_label;

    init_Table_Header();
    mTotal_Profit->setText("总盈利：" + get_Current_Table_Money() + " 元");
}

void ShopPlace_Table::init_Table_Header()
{
    //初始化表头
    mTable->setColumnCount(8);
    mTable->setHorizontalHeaderLabels(
          QStringList()<<"日期" <<"时间" <<"出账号"<<"出账账户"
                       <<"入账号"<<"入账账户"<<"金额"<<"流水号");
    mTable->horizontalHeader()->setStretchLastSection(true); //就是这个地方

    int RowCount = 0;
    Information* iter = mCCMIS->GetInfoPointer() ->next;


    int cur_num = mCCMIS->GetUserNum();

    if(cur_num%1000 == 0){
        while(iter!=NULL){
            if (((int)iter->Inumber > cur_num) && ((int)iter->Inumber < (cur_num+1000)) ) {
                show_One_Info_All(iter,RowCount);
            }
            iter  = iter->next;
        }
    }else if(cur_num%100 == 0){
        while(iter!=NULL){
            if (((int)iter->Inumber > cur_num) && ((int)iter->Inumber < (cur_num+100)) ) {
                show_One_Info_All(iter,RowCount);
            }
            iter  = iter->next;
        }
    }
}




void ShopPlace_Table::on_Filter_clicked_SP()
{
    this->Table_Filtered_By_Date(mTable);
    this->mTotal_Profit->setText("总盈利：" + get_Current_Table_Money() + " 元");
}


void ShopPlace_Table::on_Reset_clicked_SP()
{
    this->mTable->setRowCount(0);
    this->mTable->clear();
    this->init_Table_Header();
    this->mTotal_Profit->setText("总盈利：" + get_Current_Table_Money() + " 元");
}


//---------------------------------------------------------------------
//-----------------------------------------------------------用户类子函数
User_Table::User_Table(QTableWidget *table, QDateEdit* start_edit,
                       QDateEdit* finish_edit, QPushButton* filter_btn,
                       QPushButton* reset_btn, QPushButton* export_btn,
                       CCMIS* ccmis_sys, QCheckBox *subsidy_check)
        :Table_Parent(table, start_edit,finish_edit,filter_btn,
                    reset_btn, export_btn,ccmis_sys) {
    mSubsidy_Chck = subsidy_check;
    mCurrent_User = mCCMIS->GetCurrentUser();
    init_Table_Header();
}

void User_Table::init_Table_Header()
{
    mTable->setColumnCount(6);
    mTable->setHorizontalHeaderLabels
            (QStringList()<<"日期" <<"时间" <<"入账号"<<"入账账户"<<"金额"<<"流水号");
    mTable->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    int RowCount = 0;
    int mCurrent_User_Num = mCCMIS->GetUserNum();
    Information* iter = mCCMIS->GetInfoPointer() ->next;
    while(iter!=NULL){
       if((int)iter->Onumber == mCurrent_User_Num || (int)iter->Inumber == mCurrent_User_Num)
            show_One_Info_Same_Num(iter,RowCount,iter->Inumber);
       iter = iter->next;
    }
    return;
}

//用户类下的补助查看，只能查看自己的补助
void  User_Table::init_Subsidy_Header()
{
    mTable->setColumnCount(6);
    mTable->setHorizontalHeaderLabels(
           QStringList()<<"日期" <<"时间" <<"入帐号"<<"被补助人"<<"金额"<<"流水号");
    mTable->horizontalHeader()->setStretchLastSection(true); //就是这个地方
    int mCurrent_User_Num = mCCMIS->GetUserNum();
    int RowCount = 0;
    Information* iter = mCCMIS->GetInfoPointer() ->next;
    while(iter!=NULL){
        if(((int)iter->Onumber == 2)&& ((int)iter->Inumber == mCurrent_User_Num))
            show_One_Info_Same_Num(iter,RowCount,mCurrent_User_Num);
        iter = iter->next;
    }
    return;
}

//-----------------------------------------------------用户槽函数
void User_Table::on_Subsidy_Check_User(int state)
{
    switch (state) {
    case Qt::Checked:
        this->mTable->setRowCount(0);
        init_Subsidy_Header();
        break;
    case Qt::Unchecked:
        this->mTable->setRowCount(0);
        init_Table_Header();
        break;
    }
}

void User_Table::on_Reset_clicked(){
    if(mSubsidy_Chck->isChecked()){
        this->mTable->setRowCount(0);
        init_Subsidy_Header();
    }else{
        this->mTable->setRowCount(0);
        init_Table_Header();
    }
}
