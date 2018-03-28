#include "shopmainwindow.h"
#include "ui_shopmainwindow.h"

ShopMainWindow::ShopMainWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopMainWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());
}

ShopMainWindow::~ShopMainWindow()
{
    delete ui;
}

void ShopMainWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void ShopMainWindow::on_SearchButton_clicked()
{
    ShopSearchWindow *mASeaW = new ShopSearchWindow(mCCMIS,this);
    mASeaW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASeaW->show();
    this->hide();
}

void ShopMainWindow::on_WorkButton_clicked()
{
    ShopServiceWindow *mASerW = new ShopServiceWindow(mCCMIS,this);
    mASerW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASerW->show();
    this->hide();
}
