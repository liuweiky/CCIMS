#include "administratorscwindow.h"
#include "ui_administratorscwindow.h"

AdministratorSCWindow::AdministratorSCWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorSCWindow)
{
    ui->setupUi(this);

    //表格显示





    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

}





AdministratorSCWindow::~AdministratorSCWindow()
{
    delete ui;
}

void AdministratorSCWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void AdministratorSCWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}

void AdministratorSCWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}
