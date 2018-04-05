#include "userrechargewindow.h"
#include "ui_userrechargewindow.h"

UserRechargeWindow::UserRechargeWindow(CCMIS *c, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::UserRechargeWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    mCCMIS = c;

    //时间处理
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_dispose()));
    timer->start(500);

    refreshUi();

    //图片导入
    QIcon icon;
    std::string str = mCCMIS->FilenameCorrect
            (mCCMIS->BACKBUTTON_PICTURE_NAME).toStdString();
    const char* address = str.c_str();  //转地址QString到char*
    icon.addFile(tr(address));
    ui->BackButton->setIcon(icon);

    //限制输入
    //正则表达式，只允许输入0~9
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->moneyLineEdit);
    ui->moneyLineEdit->setValidator(validator);
}

UserRechargeWindow::~UserRechargeWindow()
{
    delete ui;
}


void UserRechargeWindow::time_dispose()
{
    ui->Time->display(AboutUI::ShowDateTime());
}

void UserRechargeWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void UserRechargeWindow::on_WorkButton_clicked()
{
    int money = ui->moneyLineEdit->text().toInt() * 100;
    if (mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->balance + money > 100000)
    {
        QMessageBox::warning(this, tr("警告！"),
                           tr("校园卡余额超过 1000！"),
                           QMessageBox::Yes);
    } else {
        if (mCCMIS->NewRecharge(mCCMIS->GetUserNum(), money))
        {
            QMessageBox* msg = new QMessageBox(this);
            msg->setText(tr("充值成功！"));
            msg->show();
        } else {
            QMessageBox* msg = new QMessageBox(this);
            msg->setText(tr("充值失败！"));
            msg->show();
        }
    }   
    refreshUi();    //更新余额等数据
}

void UserRechargeWindow::refreshUi()
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

    //更新父窗口A
    UserMainWindow* u = (UserMainWindow*)parentWidget();
    u->refreshUi();
}
