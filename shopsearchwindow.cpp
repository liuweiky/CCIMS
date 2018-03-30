#include "shopsearchwindow.h"
#include "ui_shopsearchwindow.h"
#include "information.h"
ShopSearchWindow::ShopSearchWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopSearchWindow)
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

    //表格显示

    mShopTable = new Shop_Table(ui->tableWidget,ui->StartDateEdit,
                                ui->FinishDateEdit,ui->FilterButton,
                                ui->ResetButton,ui->ExportButton,
                                mCCMIS,ui->DeleteButton,
                                ui->InsertButton,ui->AlterButton);
    connect(mShopTable->mStart_Edit,SIGNAL(dateChanged(QDate)),
            SLOT(mShopTable->on_Start_Date_Changed(QDate);));

    connect(mShopTable->mFinish_Edit,SIGNAL(dateChanged(QDate)),
            SLOT(mShopTable->on_Finish_Date_Changed(QDate);));
    connect(mShopTable->mFilter_Btn,SIGNAL(clicked(bool)),
            SLOT(mShopTable->on_Filter_clicked();));
    connect(mShopTable->mReset_Btn,SIGNAL(clicked(bool)),
            SLOT(mShopTable->on_Reset_clicked();));
    connect(mShopTable->mExport_Btn,SIGNAL(pressed()),
            SLOT(mShopTable->on_Export_pressed();));




}

ShopSearchWindow::~ShopSearchWindow()
{
    delete ui;
}




ShopSearchWindow::~ShopSearchWindow()
{
    delete ui;
}



void ShopSearchWindow::time_dispose()
{
    ui->Time->display(mCCMIS->ShowDateTime());
    //月初刷新券
    mCCMIS->CouponFresh();
}

void ShopSearchWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}
