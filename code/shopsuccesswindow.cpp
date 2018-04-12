#include "shopsuccesswindow.h"
#include "ui_shopsuccesswindow.h"

ShopSuccessWindow::ShopSuccessWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopSuccessWindow)
{
    ui->setupUi(this);
}

ShopSuccessWindow::~ShopSuccessWindow()
{
    delete ui;
}

void ShopSuccessWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopSuccessWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}
