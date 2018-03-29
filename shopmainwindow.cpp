#include "shopmainwindow.h"
#include "ui_shopmainwindow.h"

ShopMainWindow::ShopMainWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopMainWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

    //时间处理
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_dispose()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());

    //图片导入
    QIcon icon;
    std::string str = mCCMIS->FilenameCorrect
            (mCCMIS->BACKBUTTON_PICTURE_NAME).toStdString();
    const char* address = str.c_str();  //转地址QString到char*
    icon.addFile(tr(address));
    ui->BackButton->setIcon(icon);

}

ShopMainWindow::~ShopMainWindow()
{
    delete ui;
}

void ShopMainWindow::time_dispose()
{
    ui->Time->display(mCCMIS->ShowDateTime());
    //月初刷新券
    mCCMIS->CouponFresh();
}

void ShopMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void ShopMainWindow::on_SearchButton_clicked()
{
    ShopSearchWindow *mASeaW = new ShopSearchWindow(mCCMIS,this);
    mASeaW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASeaW->show();
    this->hide();
}

void ShopMainWindow::on_WorkButton_clicked()
{
    ShopServiceWindow *mASerW = new ShopServiceWindow(mCCMIS,this);
    mASerW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASerW->show();
    this->hide();
}
