#include "shopmainwindow.h"
#include "ui_shopmainwindow.h"

ShopMainWindow::ShopMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopMainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);
}

ShopMainWindow::~ShopMainWindow()
{
    delete ui;
}

void ShopMainWindow::on_BackButton_clicked()
{
    BackMainWindow();
    this->close();
}

void ShopMainWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopMainWindow::showname(QString txtname)
{
    ui->UserName->setText(txtname);
}

void ShopMainWindow::on_SearchButton_clicked()
{

}
