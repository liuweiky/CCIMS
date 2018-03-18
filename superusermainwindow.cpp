#include "superusermainwindow.h"
#include "ui_superusermainwindow.h"

SuperuserMainWindow::SuperuserMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperuserMainWindow)
{
    ui->setupUi(this);
}

SuperuserMainWindow::~SuperuserMainWindow()
{
    delete ui;
}
