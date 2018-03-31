#include "administratorscwindow.h"
#include "ui_administratorscwindow.h"

AdministratorSCWindow::AdministratorSCWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorSCWindow)
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

    mAdminTable = new Admin_Table(ui->tableWidget,ui->StartDateEdit,
                                  ui->FinishDateEdit,ui->FilterButton,
                                  ui->resetButton,ui->ExportButton,mCCMIS,
                                  ui->DeleteButton,ui->InsertButton,
                                  ui->AlterButton,ui->CheckForSubsidy);

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
            SLOT(mAdminTable->on_Subsidy_Check_Admin(int)));

    //当前选中的条目索引
    mCurrentItem = -1;

}




AdministratorSCWindow::~AdministratorSCWindow()
{
    delete ui;
}

void AdministratorSCWindow::time_dispose()
{
    ui->Time->display(mCCMIS->ShowDateTime());
    //月初刷新券
    mCCMIS->CouponFresh();
}

void AdministratorSCWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void AdministratorSCWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    mAdminTable->mCurrentItemIndex = item->row();
}

void AdministratorSCWindow::on_DeleteButton_clicked()
{
    mAdminTable->DelItem();
}
