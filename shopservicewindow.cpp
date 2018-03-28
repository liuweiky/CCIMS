#include "shopservicewindow.h"
#include "ui_shopservicewindow.h"

ShopServiceWindow::ShopServiceWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopServiceWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());

    QRegExp regx("[0-9]+$");    //正则表达式，只允许输入0~9
    QValidator *validator = new QRegExpValidator(regx, ui->CardNumLineEdit);
    ui->CardNumLineEdit->setValidator(validator);

    QDoubleValidator* v = new QDoubleValidator;
    ui->MoneyLineEdit->setValidator(v);

}

ShopServiceWindow::~ShopServiceWindow()
{
    delete ui;
}

void ShopServiceWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void ShopServiceWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void ShopServiceWindow::on_WorkButton_clicked()
{
    int onum = ui->CardNumLineEdit->text().toInt();
    int money = ui->MoneyLineEdit->text().toDouble() * 100; //*100

    //mCCMIS->NewTransaction(onum, mCCMIS->GetUserNum(), money);

    switch (mCCMIS->NewTransaction(onum, mCCMIS->GetUserNum(), money)) {
    case -1:
        QMessageBox::warning(this, tr("警告！"),
                           tr("没有该用户！"),
                           QMessageBox::Yes);
        break;
    case -2:
        QMessageBox::warning(this, tr("警告！"),
                           tr("商铺不存在！"),
                           QMessageBox::Yes);
        break;
    case -3:
        QMessageBox::warning(this, tr("警告！"),
                           tr("单日额度已用尽或超过单笔限制！"),
                           QMessageBox::Yes);
        break;
    case -4:
        QMessageBox::warning(this, tr("警告！"),
                           tr("余额不足！"),
                           QMessageBox::Yes);
        break;
    case -5:
        QMessageBox::warning(this, tr("警告！"),
                           tr("金额不能小于 0！"),
                           QMessageBox::Yes);
        break;
    case 0:
        QMessageBox::information(this, tr("信息！"),
                           tr("交易成功！"),
                           QMessageBox::Yes);
        break;
    default:
        break;
    }
}
