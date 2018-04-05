#include "shopservicewindow.h"
#include "ui_shopservicewindow.h"

ShopServiceWindow::ShopServiceWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopServiceWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    mCCMIS = c;

    //时间处理
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_dispose()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCMIS->GetCurrentUserName());

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
    QValidator *validator = new QRegExpValidator(regx, ui->CardNumLineEdit);
    ui->CardNumLineEdit->setValidator(validator);
    QDoubleValidator* v = new QDoubleValidator;
    ui->MoneyLineEdit->setValidator(v);
}

ShopServiceWindow::~ShopServiceWindow()
{
    delete ui;
}

void ShopServiceWindow::time_dispose()
{
    ui->Time->display(AboutUI::ShowDateTime());
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
