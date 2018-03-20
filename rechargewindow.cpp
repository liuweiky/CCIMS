#include "rechargewindow.h"
#include "ui_rechargewindow.h"

RechargeWindow::RechargeWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RechargeWindow)
{
    ui->setupUi(this);
    mCCMIS = c;

    QRegExp regx("[0-9]+$");    //正则表达式，只允许输入0~9
    QValidator *validator = new QRegExpValidator(regx, ui->moneyLineEdit);
    ui->moneyLineEdit->setValidator(validator);
}

RechargeWindow::~RechargeWindow()
{
    delete ui;
}

void RechargeWindow::on_rechargeButton_clicked()
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
            QMessageBox* msg = new QMessageBox();
            msg->setText(tr("充值成功！"));
            msg->show();
        } else {
            QMessageBox* msg = new QMessageBox();
            msg->setText(tr("充值失败！"));
            msg->show();
        }
    }
}
