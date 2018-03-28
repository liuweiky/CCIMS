#include "administratorscwindow.h"
#include "ui_administratorscwindow.h"

AdministratorSCWindow::AdministratorSCWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorSCWindow)
{
    ui->setupUi(this);

    mCCMIS = c;

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
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

    //表格显示

}

AdministratorSCWindow::~AdministratorSCWindow()
{
    delete ui;
}

void AdministratorSCWindow::showtime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txtTime =date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    ui->Time->display(txtTime);
}

void AdministratorSCWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}
