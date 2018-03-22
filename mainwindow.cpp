#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSMW = new ShopMainWindow;
    connect(mSMW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),mSMW,SLOT(ShowNameSlot(QString)));

    mCCMIS = new CCMIS();

    QRegExp regx("[0-9]+$");    //正则表达式，只允许输入0~9
    QValidator *validator = new QRegExpValidator(regx, ui->UserNameLineEdit);
    ui->UserNameLineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reshow(int x,int y,int w,int l){
    this->setGeometry(x,y,w,l);
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    int number = ui->UserNameLineEdit->text().toInt();

    mCCMIS->SetUserNumber(number);

    if (mCCMIS->CheckPassword(
                ui->PasswordLineEdit->text().toStdString()))
    {
        QMessageBox msg;

        if (number <= CCMIS::SUPERUSER_END)
        {
            msg.setText(tr("登录成功！\n 你是：管理员"));
            Info_Table* AllInfo = new Info_Table(mCCMIS);
            AllInfo->show();
        } else if (number <= CCMIS::SHOP_END){
            msg.setText(tr("登录成功！\n 你是：店家"));
            mSMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mSMW->show();
        } else {
            msg.setText(tr("登录成功！\n 你是：学生/教职工"));
            UserMainWindow* umw = new UserMainWindow(mCCMIS);
            umw->show();
        }
<<<<<<< HEAD
    ShowNameSignal("陆子旭");
=======

        if (number <= CCMIS::SUPERUSER_END)
        {
            msg.setText(tr("登录成功！\n 你是：管理员"));
            Info_Table* AllInfo = new Info_Table(mCCMIS);
            AllInfo->show();
        } else if (number <= CCMIS::SHOP_END){
            msg.setText(tr("登录成功！\n 你是：店家"));
            mSMW->show();
        } else {
            msg.setText(tr("登录成功！\n 你是：学生/教职工"));
        }
>>>>>>> 5a4b58ac29caf47e45dd6071304b4930e70d0395
    this->hide();

        //msg.exec();
    } else {

         //可以有错误提示音
        QMessageBox::warning(this, tr("警告！"),
                           tr("用户名或密码错误！"),
                           QMessageBox::Yes);
        ui->UserNameLineEdit->clear();
        ui->PasswordLineEdit->clear();
        ui->UserNameLineEdit->setFocus();
    }
}
