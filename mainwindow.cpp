#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCCMIS = new CCMIS();

    mUMW = new UserMainWindow(mCCMIS);
    connect(mUMW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mUMW,SLOT(ShowNameSlot(QString)));
    connect(this,SIGNAL(ShowMoneySignal(double)),
            mUMW,SLOT(ShowMoneySlot(double)));
    connect(this,SIGNAL(ShowCouponSignal(double)),
            mUMW,SLOT(ShowCouponSlot(double)));
    mPMW = new PlaceMainWindow;
    connect(mPMW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mPMW,SLOT(ShowNameSlot(QString)));
    mSMW = new ShopMainWindow(mCCMIS);
    connect(mSMW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mSMW,SLOT(ShowNameSlot(QString)));
    mAMW = new AdministratorMainWindow;
    connect(mAMW,SIGNAL(BackMainWindow(int,int,int,int)),
            this,SLOT(reshow(int,int,int,int)));
    connect(this,SIGNAL(ShowNameSignal(QString)),
            mAMW,SLOT(ShowNameSlot(QString)));



    QRegExp regx("[0-9]+$");    //正则表达式，只允许输入0~9
    QValidator *validator = new QRegExpValidator(regx, ui->UserNameLineEdit);
    ui->UserNameLineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reshow(int x,int y,int w,int l){
    //this->setGeometry(x,y,w,l);
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
            Info_Table* info = new Info_Table(mCCMIS);
            info->show();
//            mAMW->setGeometry(this->x(),this->y(),this->width(),this->height());
//            mAMW->show();
        } else if (number <= CCMIS::SHOP_END){
            msg.setText(tr("登录成功！\n 你是：店家"));
            //mSMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mSMW->show();
        } else {
            msg.setText(tr("登录成功！\n 你是：学生/教职工"));
            //mUMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mUMW->show();
            //这里要给余额和劵
            ShowMoneySignal(98);
            ShowMoneySignal(233);
        }

    //这里需要用户名
    ShowNameSignal("陆子旭");

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
