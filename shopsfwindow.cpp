#include "shopsfwindow.h"
#include "ui_shopsfwindow.h"

ShopSFWindow::ShopSFWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopSFWindow)
{
    ui->setupUi(this);
}

ShopSFWindow::~ShopSFWindow()
{
    delete ui;
}

void ShopSFWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopSFWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}
