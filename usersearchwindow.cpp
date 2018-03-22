#include "usersearchwindow.h"
#include "ui_usersearchwindow.h"

UserSearchWindow::UserSearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserSearchWindow)
{
    ui->setupUi(this);
}

UserSearchWindow::~UserSearchWindow()
{
    delete ui;
}
