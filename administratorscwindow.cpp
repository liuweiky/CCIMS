#include "administratorscwindow.h"
#include "ui_administratorscwindow.h"
#include "table_funcs.h"

AdministratorSCWindow::AdministratorSCWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorSCWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

    //时间处理
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_dispose()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());

    //图片导入
    QIcon icon;
    std::string str = mCCMIS->FilenameCorrect
            (mCCMIS->BACKBUTTON_PICTURE_NAME).toStdString();
    const char* address = str.c_str();  //转地址QString到char*
    icon.addFile(tr(address));
    ui->BackButton->setIcon(icon);

    //表格显示
    Admin_Table(ui->tableWidget,ui->StartDateEdit,ui->FinishDateEdit,
                ui->filterButton,ui->resetButton,ui->OutputButton,mCCMIS,
                ui->deletebutton,ui->insertButton,ui->alterButton,ui->checkForSubsidy);

    //当前选中的条目索引
    mCurrentItem = -1;

}

AdministratorSCWindow::~AdministratorSCWindow()
{
    delete ui;
}

void AdministratorSCWindow::time_dispose()
{
    ui->Time->display(mCCMIS->ShowDateTime());
    //月初刷新券
    mCCMIS->CouponFresh();
}

void AdministratorSCWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void AdministratorSCWindow::on_deletebutton_clicked()
{
    if (mCurrentItem != -1)
    {
        QString tag = "";
        QString date = ui->tableWidget->item(mCurrentItem, 0)->text().replace(QString("-"),QString(""));
        QString time = ui->tableWidget->item(mCurrentItem, 1)->text().replace(QString(":"),QString(""));
        QString onum = ui->tableWidget->item(mCurrentItem, 2)->text();
        QString inum = ui->tableWidget->item(mCurrentItem, 5)->text();
        int money = ui->tableWidget->item(mCurrentItem, 6)->text().toDouble()*100;

        tag = date + time + onum + inum;

        if (money < 10)
        {
            tag += "0000" + QString::number (money);
        } else if (money < 100)
        {
            tag += "000" + QString::number (money);
        } else if (money < 1000)
        {
            tag += "00" + QString::number (money);
        } else if (money < 10000)
        {
            tag += "0" + QString::number (money);
        } else {
            tag += QString::number (money);
        }


        qDebug()<<tag;

        Information* info = mCCMIS->GetInfoByTag(tag);

        if (info == NULL)
        {
            tag = date + time + onum + inum;
            money = ui->tableWidget->item(mCurrentItem, 6)->text().toDouble()*100 + 1;  //防止出现double转int被去尾

            tag = date + time + onum + inum;

            if (money < 10)
            {
                tag += "0000" + QString::number (money);
            } else if (money < 100)
            {
                tag += "000" + QString::number (money);
            } else if (money < 1000)
            {
                tag += "00" + QString::number (money);
            } else if (money < 10000)
            {
                tag += "0" + QString::number (money);
            } else {
                tag += QString::number (money);
            }

            qDebug()<<tag;
            info = mCCMIS->GetInfoByTag(tag);
        }

        mCCMIS->NewRefund(info);
        ui->tableWidget->removeRow(mCurrentItem);
        mCurrentItem = -1;

        QMessageBox::information(this, tr("提示"),
                           tr("删除成功！"),
                           QMessageBox::Yes);
    }
}

void AdministratorSCWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    mCurrentItem = item->row();
}
