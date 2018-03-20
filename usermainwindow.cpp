#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QDebug>

UserMainWindow::UserMainWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    mCCMIS = c;
    User* u = mCCMIS->GetUserByNum(mCCMIS->GetUserNum());

    ui->welcomeLabel->setText(QString(str2qstr(u->name) + "同学， 欢迎您！"));
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::on_rechargeButton_clicked()
{
    RechargeWindow* rw = new RechargeWindow(mCCMIS);
    rw->show();
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
