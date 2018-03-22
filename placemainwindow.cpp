#include "placemainwindow.h"
#include "ui_placemainwindow.h"

PlaceMainWindow::PlaceMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlaceMainWindow)
{
    ui->setupUi(this);

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);
}

PlaceMainWindow::~PlaceMainWindow()
{
    delete ui;
}

void PlaceMainWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void PlaceMainWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}

void PlaceMainWindow::ShowMoneySlot(double money)
{
    ui->money->setText("总盈利:"+QString::number(money)+"元");
}

void PlaceMainWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}
