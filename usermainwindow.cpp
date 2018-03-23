#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QDebug>

UserMainWindow::UserMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    //窗口跳转
    mUSW = new UserSearchWindow;
    connect(mUSW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mUSW,SLOT(ShowNameSlot(QString)));
    connect(this,SIGNAL(ShowMoneySignal(double)),
            mUSW,SLOT(ShowMoneySlot(double)));

    mURW = new UserRechargeWindow;
    connect(mURW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mURW,SLOT(ShowNameSlot(QString)));
    connect(this,SIGNAL(ShowMoneySignal(double)),
            mURW,SLOT(ShowMoneySlot(double)));

    mCCMIS = new CCMIS();
    User* u = mCCMIS->GetUserByNum(mCCMIS->GetUserNum());
    ui->welcomeLabel->setText(QString(str2qstr(u->name) + "同学， 欢迎您！"));
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}


QString UserMainWindow::str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string UserMainWindow::qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

void UserMainWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void UserMainWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}

void UserMainWindow::ShowMoneySlot(double money)
{
    ui->Money->setText("余额:"+QString::number(money)+"元");
}

void UserMainWindow::ShowCouponSlot(double money)
{
    ui->Coupon->setText("劵:"+QString::number(money)+"元");
}

void UserMainWindow::reshow(int x,int y,int w,int l){
    this->setGeometry(x,y,w,l);
    this->show();
}

void UserMainWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}

void UserMainWindow::on_SearchButton_clicked()
{
    mUSW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mUSW->show();
    ShowNameSignal(ui->UserName->text());
    //这里要钱数
    ShowMoneySignal(233);
    this->hide();
}

void UserMainWindow::on_WorkButton_clicked()
{
    mURW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mURW->show();
    ShowNameSignal(ui->UserName->text());
    //这里要钱数
    ShowMoneySignal(233);
    this->hide();
}
