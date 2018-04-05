#include "administratormainwindow.h"
#include "ui_administratormainwindow.h"

AdministratorMainWindow::AdministratorMainWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorMainWindow)
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
}

AdministratorMainWindow::~AdministratorMainWindow()
{
    delete ui;
}

void AdministratorMainWindow::time_dispose()
{
    ui->Time->display(AboutUI::ShowDateTime());
}

void AdministratorMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void AdministratorMainWindow::on_ImportButton_clicked()
{
    AdministratorLeadWindow *mALW = new AdministratorLeadWindow(mCCMIS,this);
    mALW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mALW->show();
    this->hide();
}

void AdministratorMainWindow::on_WorkButton_clicked()
{
    //进度条展示
    QProgressDialog *progressDlg = new
            QProgressDialog(QStringLiteral("正在载入文件......"),
                            QStringLiteral("等待"),0,mCCMIS->GuessTotalNumber,this);
    if(!AboutUI::PDlg(progressDlg,mCCMIS,mCCMIS->GuessTotalNumber)){
        return;
    }

    //产生界面
    AdministratorSCWindow *mASCW = new AdministratorSCWindow(mCCMIS,this);
    mASCW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASCW->show();
    this->hide();
}
