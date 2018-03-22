#include "administratorsfwindow.h"
#include "ui_administratorsfwindow.h"

AdministratorSFWindow::AdministratorSFWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorSFWindow)
{
    ui->setupUi(this);
}

AdministratorSFWindow::~AdministratorSFWindow()
{
    delete ui;
}
