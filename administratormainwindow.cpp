#include "administratormainwindow.h"
#include "ui_administratormainwindow.h"

AdministratorMainWindow::AdministratorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorMainWindow)
{
    ui->setupUi(this);


    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    //窗口跳转
    mALW = new AdministratorLeadWindow;
    connect(mALW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    /*connect(this,SIGNAL(ShowNameSignal(QString)),
             mALW,SLOT(ShowNameSlot(QString)));*/

    mASCW = new AdministratorSCWindow;
    connect(mASCW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mASCW,SLOT(ShowNameSlot(QString)));
}

AdministratorMainWindow::~AdministratorMainWindow()
{
    delete ui;
}

void AdministratorMainWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void AdministratorMainWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}


void AdministratorMainWindow::reshow(int x,int y,int w,int l){
    this->setGeometry(x,y,w,l);
    this->show();
}

void AdministratorMainWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}

void AdministratorMainWindow::on_ImportButton_clicked()
{
    mALW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mALW->show();
    ShowNameSignal(ui->UserName->text());
    this->hide();
}

void AdministratorMainWindow::on_WorkButton_clicked()
{
    mASCW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASCW->show();
    ShowNameSignal(ui->UserName->text());
    this->hide();
}


