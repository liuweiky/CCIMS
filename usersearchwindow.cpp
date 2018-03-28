#include "usersearchwindow.h"
#include "ui_usersearchwindow.h"

UserSearchWindow::UserSearchWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserSearchWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);
}

UserSearchWindow::~UserSearchWindow()
{
    delete ui;
}

void UserSearchWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void UserSearchWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}
