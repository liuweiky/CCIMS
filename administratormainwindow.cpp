#include "administratormainwindow.h"
#include "ui_administratormainwindow.h"

AdministratorMainWindow::AdministratorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorMainWindow)
{
    ui->setupUi(this);
}

AdministratorMainWindow::~AdministratorMainWindow()
{
    delete ui;
}
