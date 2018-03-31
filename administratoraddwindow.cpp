#include "administratoraddwindow.h"
#include "ui_administratoraddwindow.h"

AdministratorAddWindow::AdministratorAddWindow(CCMIS* c, int ismod, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorAddWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

    isModify = ismod;

    //正则表达式，只允许输入0~9
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->InumEdit);
    ui->InumEdit->setValidator(validator);

    validator = new QRegExpValidator(regx, ui->OnumEdit);
    ui->OnumEdit->setValidator(validator);

    QDoubleValidator* v = new QDoubleValidator;
    ui->MoneyEdit->setValidator(v);

    ui->dateTimeEdit->setMaximumDateTime(QDateTime::currentDateTime());
}

AdministratorAddWindow::~AdministratorAddWindow()
{
    delete ui;
}

void AdministratorAddWindow::on_AddButton_clicked()
{
    int inum = ui->InumEdit->text().toInt();
    int onum = ui->OnumEdit->text().toInt();
    int money = ui->MoneyEdit->text().toDouble() * 100; //*100

    QDateTime dt= ui->dateTimeEdit->dateTime();

    int year = dt.date().year();
    int month = dt.date().month();
    int day = dt.date().day();

    QTime qt= ui->dateTimeEdit->time();

    int hour = qt.hour();
    int min = qt.minute();
    int sec = qt.second();

    //mCCMIS->NewTransaction(onum, mCCMIS->GetUserNum(), money);

    switch (mCCMIS->NewAdmTransaction(year, month, day, hour, min, sec, onum, inum, money)) {
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
                           tr("创建成功！"),
                           QMessageBox::Yes);
        if (isModify)
        {
            AdministratorSCWindow* a = (AdministratorSCWindow*)parentWidget();
            a->ModItem(year, month, day, hour, min, sec, onum, inum, money);
        }
        break;
    default:
        break;
    }
}
