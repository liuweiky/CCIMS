 #include "administratoradddialog.h"
#include "ui_administratoradddialog.h"
#include "administratorscwindow.h"
AdministratorAddDialog::AdministratorAddDialog(CCIMS* c, int ismod, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdministratorAddDialog)
{
    ui->setupUi(this);

    mCCIMS = c;
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

    mCur_Inum_Btn = ui->Cur_Inum_Btn;
    mCur_Onum_Btn = ui->Cur_Onum_Btn;

    //限制输入设置
    //正则表达式，只允许输入0~9
    QRegExp regx("[0-9]+$");

    QValidator* validator;
    //出账、入账输入
    validator = new QRegExpValidator(regx, ui->InumEdit);
    ui->InumEdit->setValidator(validator);
    validator = new QRegExpValidator(regx, ui->OnumEdit);
    ui->OnumEdit->setValidator(validator);
    //金额输入
    QDoubleValidator* v = new QDoubleValidator;
    v->setDecimals(2);
    ui->MoneyEdit->setValidator(v);
}



AdministratorAddDialog::~AdministratorAddDialog()
{
    delete ui;
}

void AdministratorAddDialog::on_buttonBox_accepted()
{
    //读取数据
    int inum = ui->InumEdit->text().toInt();
    int onum = ui->OnumEdit->text().toInt();
    int money = ui->MoneyEdit->text().toDouble() * 100.001; //*100
    int year = mDate->year();
    int month = mDate->month();
    int day = mDate->day();
    int hour = mTime->hour();
    int min = mTime->minute();
    int sec = mTime->second();

    //传参数至主界面
    AdministratorSCWindow* a = (AdministratorSCWindow*)parentWidget();
    switch (mCCIMS->NewAdmTransaction(year, month, day, hour, min, sec, onum, inum, money)) {   //Adm可以超过单日限制
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
                           tr("金额小于 0 或格式错误！"),
                           QMessageBox::Yes);
        break;
    case -7:
        QMessageBox::warning(a, tr("警告！"),
                           tr("重复插入！"),
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

void AdministratorAddDialog::setInOutNumEnable(bool state)
{
    mCur_Inum_Btn->setEnabled(state);
    mCur_Onum_Btn->setEnabled(state);
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

void AdministratorAddDialog::on_Cur_Onum_Btn_stateChanged(int arg1)
{
    AdministratorSCWindow   * p = (AdministratorSCWindow*) parentWidget();
    switch(arg1){
    case Qt::Checked:
        ui->OnumEdit->setEnabled(false);
        ui->OnumEdit->setText(p->GetTable()->get_Current_Row_Onum());
        qDebug()<<ui->OnumEdit->text();
        break;
    case Qt::Unchecked:
        ui->OnumEdit->setEnabled(true);
        break;
    }
}

void AdministratorAddDialog::on_Cur_Inum_Btn_stateChanged(int arg1)
{
    AdministratorSCWindow   * p = (AdministratorSCWindow*) parentWidget();
    switch(arg1){
    case Qt::Checked:
        ui->InumEdit->setEnabled(false);
        ui->InumEdit->setText(p->GetTable()->get_Current_Row_Inum());
        qDebug()<<ui->InumEdit->text();
        break;
    case Qt::Unchecked:
        ui->InumEdit->setEnabled(true);
        break;
    }
}
