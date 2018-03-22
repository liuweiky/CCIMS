#include "shopmainwindow.h"
#include "ui_shopmainwindow.h"

ShopMainWindow::ShopMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopMainWindow)
{
    ui->setupUi(this);

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    //窗口跳转
    mSSearchW = new ShopSearchWindow;
    connect(mSSearchW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),mSSearchW,SLOT(ShowNameSlot(QString)));

    mSServiceW = new ShopServiceWindow;
    connect(mSServiceW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),mSServiceW,SLOT(ShowNameSlot(QString)));
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

void ShopMainWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}


void ShopMainWindow::reshow(int x,int y,int w,int l){
    this->setGeometry(x,y,w,l);
    this->show();
}

void ShopMainWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}

void ShopMainWindow::on_SearchButton_clicked()
{
    mSSearchW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mSSearchW->show();
    ShowNameSignal(ui->UserName->text());
    this->hide();
}

void ShopMainWindow::on_WorkButton_clicked()
{
    mSServiceW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mSServiceW->show();
    ShowNameSignal(ui->UserName->text());
    this->hide();
}
