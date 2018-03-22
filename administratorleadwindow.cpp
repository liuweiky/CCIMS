#include "administratorleadwindow.h"
#include "ui_administratorleadwindow.h"

AdministratorLeadWindow::AdministratorLeadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorLeadWindow)
{
    ui->setupUi(this);
}

AdministratorLeadWindow::~AdministratorLeadWindow()
{
    delete ui;
}
