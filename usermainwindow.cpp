#include "usermainwindow.h"
#include "ui_usermainwindow.h"


usermainwindow::usermainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usermainwindow)
{
    ui->setupUi(this);
}

usermainwindow::~usermainwindow()
{
    delete ui;
}

