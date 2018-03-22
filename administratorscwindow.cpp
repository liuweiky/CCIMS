#include "administratorscwindow.h"
#include "ui_administratorscwindow.h"

AdministratorSCWindow::AdministratorSCWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorSCWindow)
{
    ui->setupUi(this);
}

AdministratorSCWindow::~AdministratorSCWindow()
{
    delete ui;
}
