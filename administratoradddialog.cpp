#include "administratoradddialog.h"
#include "ui_administratoradddialog.h"

AdministratorAddDialog::AdministratorAddDialog(CCMIS* c, int ismod, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdministratorAddDialog)
{
    ui->setupUi(this);

    mCCMIS = c;
    mDate = new QDate();
    mTime = new QTime();
    isModify = ismod;

    //时间窗口设置
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->calendarPopup();//弹出日历
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->timeEdit_2->setMaximumTime(QTime::currentTime());

    mDate->setDate(ui->dateEdit->date().year(),
                   ui->dateEdit->date().month(),ui->dateEdit->date().day());
    mTime->setHMS(ui->timeEdit_2->time().hour(),
                  ui->timeEdit_2->time().second(),0);

    //正则表达式，只允许输入0~9
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->InumEdit);
    ui->InumEdit->setValidator(validator);

    validator = new QRegExpValidator(regx, ui->OnumEdit);
    ui->OnumEdit->setValidator(validator);

    QDoubleValidator* v = new QDoubleValidator;
    ui->MoneyEdit->setValidator(v);
}

AdministratorAddDialog::~AdministratorAddDialog()
{
    delete ui;
}

void AdministratorAddDialog::on_buttonBox_accepted()
{
    int inum = ui->InumEdit->text().toInt();
    int onum = ui->OnumEdit->text().toInt();
    int money = ui->MoneyEdit->text().toDouble() * 100.001; //*100

    //QDate dt= ui->dateEdit->date();

    int year = mDate->year();
    int month = mDate->month();
    int day = mDate->day();

    //QTime qt= ui->timeEdit_2->time();

    int hour = mTime->hour();
    int min = mTime->minute();
    int sec = mTime->second();

    AdministratorSCWindow* a = (AdministratorSCWindow*)parentWidget();

    switch (mCCMIS->NewAdmTransaction(year, month, day, hour, min, sec, onum, inum, money)) {   //Adm可以超过单日限制
    case -1:
        QMessageBox::warning(a, tr("警告！"),
                           tr("没有该用户！"),
                           QMessageBox::Yes);
        break;
    case -2:
        QMessageBox::warning(a, tr("警告！"),
                           tr("商铺不存在！"),
                           QMessageBox::Yes);
        break;
    case -3:
        QMessageBox::warning(a, tr("警告！"),
                           tr("单日额度已用尽或超过单笔限制！"),
                           QMessageBox::Yes);
        break;
    case -4:
        QMessageBox::warning(a, tr("警告！"),
                           tr("余额不足！"),
                           QMessageBox::Yes);
        break;
    case -5:
        QMessageBox::warning(a, tr("警告！"),
                           tr("金额不能小于 0！"),
                           QMessageBox::Yes);
        break;
    case 0:
        QMessageBox::information(a, tr("信息！"),
                           tr("创建成功！"),
                           QMessageBox::Yes);
        if (isModify)
        {
            a->GetTable()->DelItem();
        }
        a->UpdateItem();
        break;
    default:
        break;
    }
}

void AdministratorAddDialog::on_buttonBox_rejected()
{
    this->close();
}

void AdministratorAddDialog::on_checkForCurTime_stateChanged(int arg1)
{
    QTime qt = QTime::currentTime();
    QDate qd = QDate::currentDate();
    switch (arg1) {
    case Qt::Checked:
        ui->dateEdit->setEnabled(false);
        ui->timeEdit_2->setEnabled(false);
        mTime->setHMS(qt.hour(),qt.minute(),qt.second());
        mDate->setDate(qd.year(),qd.month(),qd.day());
        break;
    case Qt::Unchecked:
        ui->dateEdit->setEnabled(true);
        ui->timeEdit_2->setEnabled(true);
        break;
    }
}

void AdministratorAddDialog::on_dateEdit_dateChanged(const QDate &date)
{
    mDate->setDate(date.year(),date.month(),date.day());
}



void AdministratorAddDialog::on_timeEdit_2_timeChanged(const QTime &time)
{
    mTime->setHMS(time.hour(),time.minute(),0);
}
