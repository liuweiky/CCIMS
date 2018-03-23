#include "userrechargewindow.h"
#include "ui_userrechargewindow.h"

UserRechargeWindow::UserRechargeWindow(QWidget *parent) :
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
