#include "usersearchwindow.h"
#include "ui_usersearchwindow.h"

UserSearchWindow::UserSearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserSearchWindow)
{
    ui->setupUi(this);

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

}

UserSearchWindow::~UserSearchWindow()
{
    delete ui;
}

void UserSearchWindow::showtime()
{
    //或者大改，或者只能在这个定时刷新函数内更新用户名（因为构造函数只会调用一次，过早构造了这个窗口，而CCMIS此时未初始化用户（-1），会导致空指针，且无法再次调用构造函数。。。
    /*if (mCCMIS->GetUserByNum(mCCMIS->GetUserNum()) != NULL)
    {
        ui->UserName->setText(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->name);
        ui->Money->setText(QString::number(double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->balance)/100));
        ui->Coupon->setText(QString::number(double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->coupon)/100));
    }*/
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void UserSearchWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}

void UserSearchWindow::ShowMoneySlot(double money)
{
    ui->Money->setText("余额:"+QString::number(money)+"元");
}

void UserSearchWindow::ShowCouponSlot(double money)
{
    ui->Coupon->setText("劵:"+QString::number(money)+"元");
}

void UserSearchWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}
