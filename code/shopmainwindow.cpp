#include "shopmainwindow.h"
#include "ui_shopmainwindow.h"

ShopMainWindow::ShopMainWindow(CCIMS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopMainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    mCCIMS = c;

    //时间处理
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_dispose()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCIMS->GetCurrentUserName());

    //图片导入
    QIcon icon;
    std::string str = mCCIMS->FilenameCorrect
            (mCCIMS->BACKBUTTON_PICTURE_NAME).toStdString();
    const char* address = str.c_str();  //转地址QString到char*
    icon.addFile(tr(address));
    ui->BackButton->setIcon(icon);
}

ShopMainWindow::~ShopMainWindow()
{
    delete ui;
}

void ShopMainWindow::time_dispose()
{
    ui->Time->display(AboutUI::ShowDateTime());
}

void ShopMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void ShopMainWindow::on_SearchButton_clicked()
{
    //进度条展示
    QProgressDialog *progressDlg = new
            QProgressDialog(QStringLiteral("正在载入文件......"),
                            QStringLiteral("等待"),0,mCCIMS->GuessTotalNumber,this);
    if(!AboutUI::PDlg(progressDlg,mCCIMS,mCCIMS->GuessTotalNumber)){
        return;
    }

    //产生界面
    ShopSearchWindow *mASeaW = new ShopSearchWindow(mCCIMS,this);
    mASeaW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASeaW->show();
    this->hide();
}

void ShopMainWindow::on_WorkButton_clicked()
{
    ShopServiceWindow *mASerW = new ShopServiceWindow(mCCIMS,this);
    mASerW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mASerW->show();
    this->hide();
}
