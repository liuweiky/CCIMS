#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCCMIS = new CCMIS();

    //正则表达式，只允许输入0~9
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->UserNameLineEdit);
    ui->UserNameLineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //获取帐号
    int number = ui->UserNameLineEdit->text().toInt();
    mCCMIS->SetUserNumber(number);

    //判断用户名和密码条件
    if (mCCMIS->CheckPassword(ui->PasswordLineEdit->text().toStdString()))
    {
        if (number <= CCMIS::SUPERUSER_END) {
            //管理员
            AdministratorMainWindow *mAMW = new AdministratorMainWindow(mCCMIS);
            mAMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mAMW->show();

//            Info_Table* info = new Info_Table(mCCMIS);
//            info->show();
        } else if (number <= CCMIS::SHOP_END) {
            //这里还需筛选
            //场所（总商家）
            PlaceMainWindow *mPMW = new PlaceMainWindow(mCCMIS);
            mPMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mPMW->show();
            //商家
            ShopMainWindow *mSMW = new ShopMainWindow(mCCMIS);
            mSMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mSMW->show();
        } else {
            //用户
            UserMainWindow *mUMW = new UserMainWindow(mCCMIS);
            mUMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mUMW->show();
        }
    this->hide();   //隐藏该窗口
    } else {
        //弹出警告窗口（可以有错误提示音）
        QMessageBox::warning(this, tr("警告！"),
                             tr("用户名或密码错误！"),
                             QMessageBox::Yes);

        //清空文字，目标回到用户名编辑
        ui->UserNameLineEdit->clear();
        ui->PasswordLineEdit->clear();
        ui->UserNameLineEdit->setFocus();
    }
}
