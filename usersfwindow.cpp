#include "usersfwindow.h"
#include "ui_usersfwindow.h"

UserSFWindow::UserSFWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserSFWindow)
{
    ui->setupUi(this);
}

UserSFWindow::~UserSFWindow()
{
    delete ui;
}
