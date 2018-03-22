#include "shopservicewindow.h"
#include "ui_shopservicewindow.h"

ShopServiceWindow::ShopServiceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopServiceWindow)
{
    ui->setupUi(this);

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    //窗口跳转
    mSSFW = new ShopSFWindow;
    connect(mSSFW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mSSFW,SLOT(ShowNameSlot(QString)));
    connect(this,SIGNAL(ShowBoolSignal(bool)),
            mSSFW,SLOT(ShowBoolSlot(bool)));
}

ShopServiceWindow::~ShopServiceWindow()
{
    delete ui;
}

void ShopServiceWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopServiceWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}

void ShopServiceWindow::reshow(int x,int y,int w,int l){
    this->setGeometry(x,y,w,l);
    this->show();
}

void ShopServiceWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}

void ShopServiceWindow::on_WorkButton_clicked()
{
    mSSFW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mSSFW->show();
    ShowNameSignal(ui->UserName->text());
     //这里要bool是否成功
    ShowBoolSignal(false);
    this->hide();
}
