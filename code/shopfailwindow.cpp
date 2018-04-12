#include "shopfailwindow.h"
#include "ui_shopfailwindow.h"

ShopFailWindow::ShopFailWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopFailWindow)
{
    ui->setupUi(this);
}

ShopFailWindow::~ShopFailWindow()
{
    delete ui;
}

void ShopFailWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopFailWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}
