#include "administratorfailwindow.h"
#include "ui_administratorfailwindow.h"

AdministratorFailWindow::AdministratorFailWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorFailWindow)
{
    ui->setupUi(this);
}

AdministratorFailWindow::~AdministratorFailWindow()
{
    delete ui;
}
