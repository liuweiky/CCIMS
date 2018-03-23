#include "administratorleadwindow.h"
#include "ui_administratorleadwindow.h"

AdministratorLeadWindow::AdministratorLeadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorLeadWindow)
{
    ui->setupUi(this);

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);
}

AdministratorLeadWindow::~AdministratorLeadWindow()
{
    delete ui;
}

void AdministratorLeadWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void AdministratorLeadWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}

void AdministratorLeadWindow::on_WorkButton_clicked()
{

}
