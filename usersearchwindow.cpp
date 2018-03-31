#include "usersearchwindow.h"
#include "ui_usersearchwindow.h"

UserSearchWindow::UserSearchWindow(CCMIS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserSearchWindow)
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
    QString Money = "余额：" + QString::number
            (double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->balance)/100,'f',2)
            + "元";
    ui->Money->setText(Money);
    QString Coupon = "劵：" + QString::number
            (double(mCCMIS->GetUserByNum(mCCMIS->GetUserNum())->coupon)/100,'f',2)
            + "元";
    ui->Coupon->setText(Coupon);

    //图片导入
    QIcon icon;
    std::string str = mCCMIS->FilenameCorrect
            (mCCMIS->BACKBUTTON_PICTURE_NAME).toStdString();
    const char* address = str.c_str();  //转地址QString到char*
    icon.addFile(tr(address));
    ui->BackButton->setIcon(icon);


    //表格显示
    mUserTable = new User_Table(ui->tableWidget,ui->StartDateEdit,
                                ui->FinishDateEdit,ui->FilterButton,
                                ui->ResetButton,ui->ExportButton,
                                mCCMIS,ui->SubsidyCheck);
    connect(mUserTable->mStart_Edit,&QDateEdit::dateChanged,
            mUserTable,&User_Table::on_Start_Date_Changed);
    connect(mUserTable->mFinish_Edit,&QDateEdit::dateChanged,
            mUserTable,&User_Table::on_Finish_Date_Changed);

    connect(mUserTable->mFilter_Btn,&QPushButton::clicked,
            mUserTable,&User_Table::on_Filter_clicked);
    connect(mUserTable->mReset_Btn,&QPushButton::clicked,
            mUserTable,&User_Table::on_Reset_clicked);
    connect(mUserTable->mExport_Btn,&QPushButton::pressed,
            mUserTable,&User_Table::on_Export_pressed);
    connect(mUserTable->mSubsidy_Chck,&QCheckBox::stateChanged,
            mUserTable,&User_Table::on_Subsidy_Check_User);

}

UserSearchWindow::~UserSearchWindow()
{
    delete ui;
}

void UserSearchWindow::time_dispose()
{
    ui->Time->display(mCCMIS->ShowDateTime());
    //月初刷新券
    mCCMIS->CouponFresh();
}

void UserSearchWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}
