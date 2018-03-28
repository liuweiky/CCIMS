#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QDebug>

UserMainWindow::UserMainWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);

    mCCMIS = c;
//    User* u = mCCMIS->GetUserByNum(mCCMIS->GetUserNum());

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());
    QString Money = "余额：" + QString::number
            (double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->balance)/100,'f',2)
            + "元";
    ui->Money->setText(Money);
    QString Coupon = "劵：" + QString::number
            (double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->coupon)/100,'f',2)
            + "元";
    ui->Coupon->setText(Coupon);
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

void UserMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void UserMainWindow::on_SearchButton_clicked()
{
    UserSearchWindow *mUSW = new UserSearchWindow(mCCMIS,this);
    mUSW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mUSW->show();
    this->hide();
}

void UserMainWindow::on_WorkButton_clicked()
{
    UserRechargeWindow *mURW = new UserRechargeWindow(mCCMIS,this);
    mURW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mURW->show();
    this->hide();
}
