#include "administratormainwindow.h"
#include "ui_administratormainwindow.h"

AdministratorMainWindow::AdministratorMainWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorMainWindow)
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

void AdministratorMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void AdministratorMainWindow::on_ImportButton_clicked()
{
    AdministratorLeadWindow *mALW = new AdministratorLeadWindow(mCCMIS,this);
    mALW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mALW->show();
    this->hide();
}

void AdministratorMainWindow::on_WorkButton_clicked()
{
    AdministratorSCWindow *mASCW = new AdministratorSCWindow(mCCMIS,this);
    mASCW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASCW->show();
    this->hide();
}
