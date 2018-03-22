#include "shopsearchwindow.h"
#include "ui_shopsearchwindow.h"

ShopSearchWindow::ShopSearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopSearchWindow)
{
    ui->setupUi(this);

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

}

ShopSearchWindow::~ShopSearchWindow()
{
    delete ui;
}

void ShopSearchWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopSearchWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}

void ShopSearchWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}
