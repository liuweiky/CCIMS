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

void ShopServiceWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}

void ShopServiceWindow::on_WorkButton_clicked()
{

}
