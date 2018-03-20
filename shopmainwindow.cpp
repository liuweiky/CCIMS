#include "shopmainwindow.h"
#include "ui_shopmainwindow.h"

ShopMainWindow::ShopMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopMainWindow)
{
    ui->setupUi(this);
}

ShopMainWindow::~ShopMainWindow()
{
    delete ui;
}

void ShopMainWindow::on_BackButton_clicked()
{
    emit BackMainWindow();
    this->close();
}
