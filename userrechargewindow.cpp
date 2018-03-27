#include "userrechargewindow.h"
#include "ui_userrechargewindow.h"

UserRechargeWindow::UserRechargeWindow(CCMIS* c, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::UserRechargeWindow)
{
    ui->setupUi(this);

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    mCCMIS = c;

    QRegExp regx("[0-9]+$");    //正则表达式，只允许输入0~9
    QValidator *validator = new QRegExpValidator(regx, ui->moneyLineEdit);
    ui->moneyLineEdit->setValidator(validator);


}

UserRechargeWindow::~UserRechargeWindow()
{
    delete ui;
}


void UserRechargeWindow::showtime()
{
    //或者大改，或者只能在这个定时刷新函数内更新用户名（因为构造函数只会调用一次，过早构造了这个窗口，而CCMIS此时未初始化用户（-1），会导致空指针，且无法再次调用构造函数。。。
    if (mCCMIS->GetUserByNum(mCCMIS->GetUserNum()) != NULL)
    {
        ui->UserName->setText(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->name);
        ui->Money->setText(QString::number(double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->balance)/100));
        ui->Coupon->setText(QString::number(double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->coupon)/100));
    }

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void UserRechargeWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}

void UserRechargeWindow::ShowMoneySlot(double money)
{
    ui->Money->setText("余额:"+QString::number(money)+"元");
}

void UserRechargeWindow::ShowCouponSlot(double money)
{
    ui->Coupon->setText("劵:"+QString::number(money)+"元");
}

void UserRechargeWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}

void UserRechargeWindow::on_WorkButton_clicked()
{
    int money = ui->moneyLineEdit->text().toInt() * 100;
    if (mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->balance + money > 100000)
    {
        QMessageBox::warning(this, tr("警告！"),
                           tr("校园卡余额超过 1000！"),
                           QMessageBox::Yes);
    } else {
        if (mCCMIS->NewRecharge(mCCMIS->GetUserNum(), money))
        {
            QMessageBox* msg = new QMessageBox();
            msg->setText(tr("充值成功！"));
            msg->show();
        } else {
            QMessageBox* msg = new QMessageBox();
            msg->setText(tr("充值失败！"));
            msg->show();
        }
    }
}
