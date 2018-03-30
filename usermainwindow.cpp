#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QDebug>

UserMainWindow::UserMainWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    mCCMIS = c;
//    User* u = mCCMIS->GetUserByNum(mCCMIS->GetUserNum());

    //时间处理
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_dispose()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());
    QString Money = "余额：" + QString::number
            (double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->balance)/100,'f',2)
            + "元";
    ui->Money->setText(Money);
    QString Coupon = "劵：" + QString::number
            (double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->coupon)/100,'f',2)
            + "元";
    ui->Coupon->setText(Coupon);

    //图片导入
    QIcon icon;
    std::string str = mCCMIS->FilenameCorrect
            (mCCMIS->BACKBUTTON_PICTURE_NAME).toStdString();
    const char* address = str.c_str();  //转地址QString到char*
    icon.addFile(tr(address));
    ui->BackButton->setIcon(icon);

}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

QString UserMainWindow::str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}
string UserMainWindow::qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

void UserMainWindow::time_dispose()
{
    ui->Time->display(mCCMIS->ShowDateTime());
    //月初刷新券
    mCCMIS->CouponFresh();
}

void UserMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void UserMainWindow::on_SearchButton_clicked()
{
    UserSearchWindow *mUSW = new UserSearchWindow(mCCMIS,this);
    mUSW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mUSW->show();
    this->hide();
}

void UserMainWindow::on_WorkButton_clicked()
{
    UserRechargeWindow *mURW = new UserRechargeWindow(mCCMIS,this);
    mURW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mURW->show();
    this->hide();
}

void UserMainWindow::refreshUi()
{
    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());
    QString Money = "余额：" + QString::number
            (double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->balance)/100,'f',2)
            + "元";
    ui->Money->setText(Money);
    QString Coupon = "劵：" + QString::number
            (double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->coupon)/100,'f',2)
            + "元";
    ui->Coupon->setText(Coupon);
}
