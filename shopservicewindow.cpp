#include "shopservicewindow.h"
#include "ui_shopservicewindow.h"

ShopServiceWindow::ShopServiceWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopServiceWindow)
{
    ui->setupUi(this);
    mCCMIS = c;

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(500);

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

void ShopServiceWindow::ShowNameSlot(QString txtname)
{
    ui->UserName->setText(txtname);
}

void ShopServiceWindow::on_BackButton_clicked()
{
    BackMainWindow(this->x(),this->y(),this->width(),this->height());
    this->close();
}

void ShopServiceWindow::on_WorkButton_clicked()
{
    int onum = ui->CardNumLineEdit->text().toInt();
    int money = ui->MoneyLineEdit->text().toDouble() * 100; //*100

    cout << mCCMIS->NewTransaction(onum, mCCMIS->GetUserNum(), money);
}
