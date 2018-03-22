#include "userrechargewindow.h"
#include "ui_userrechargewindow.h"

UserRechargeWindow::UserRechargeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserRechargeWindow)
{
    ui->setupUi(this);
}

UserRechargeWindow::~UserRechargeWindow()
{
    delete ui;
}
