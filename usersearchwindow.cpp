#include "usersearchwindow.h"
#include "ui_usersearchwindow.h"

UserSearchWindow::UserSearchWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserSearchWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

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

UserSearchWindow::~UserSearchWindow()
{
    delete ui;
}

void UserSearchWindow::time_dispose()
{
    ui->Time->display(mCCMIS->ShowDateTime());
    //月初刷新券
    mCCMIS->CouponFresh();
}

void UserSearchWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}
