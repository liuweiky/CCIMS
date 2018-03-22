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
    mSSearchW = new ShopSearchWindow;
    connect(mSSearchW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mSSearchW,SLOT(ShowNameSlot(QString)));
    connect(this,SIGNAL(ShowMoneySignal(double)),
            mSSearchW,SLOT(ShowMoneySlot(double)));

    mSServiceW = new ShopServiceWindow;
    connect(mSServiceW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mSServiceW,SLOT(ShowNameSlot(QString)));
}
}

AdministratorMainWindow::~AdministratorMainWindow()
{
    delete ui;
}
