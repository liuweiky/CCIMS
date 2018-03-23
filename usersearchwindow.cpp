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
