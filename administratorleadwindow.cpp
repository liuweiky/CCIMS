#include "administratorleadwindow.h"
#include "ui_administratorleadwindow.h"

AdministratorLeadWindow::AdministratorLeadWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorLeadWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());
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
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void AdministratorLeadWindow::on_WorkButton_clicked()
{

}
