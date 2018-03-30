#include "shopsearchwindow.h"
#include "ui_shopsearchwindow.h"
#include "information.h"
ShopSearchWindow::ShopSearchWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopSearchWindow)
{
    ui->setupUi(this);

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
    mShopTable = new Shop_Table(ui->tableWidget,ui->s)

    connect(mAdminTable->mStart_Edit,SIGNAL(dateChanged(QDate)),
            SLOT(mAdminTable->on_Start_Date_Changed(QDate);));

    connect(mAdminTable->mFinish_Edit,SIGNAL(dateChanged(QDate)),
            SLOT(mAdminTable->on_Finish_Date_Changed(QDate);));
    connect(mAdminTable->mFilter_Btn,SIGNAL(clicked(bool)),
            SLOT(mAdminTable->on_Filter_clicked();));
    connect(mAdminTable->mReset_Btn,SIGNAL(clicked(bool)),
            SLOT(mAdminTable->on_Reset_clicked();));
    connect(mAdminTable->mExport_Btn,SIGNAL(pressed()),
            SLOT(mAdminTable->on_Export_pressed();));

    connect(mAdminTable->mSubsidy_Chck,SIGNAL(stateChanged(int)),
            SLOT(mAdminTable->on_Subsidy_Check_Admin(int);));

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
