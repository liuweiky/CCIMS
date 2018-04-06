#include "placemainwindow.h"
#include "ui_placemainwindow.h"


PlaceMainWindow::PlaceMainWindow(CCMIS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlaceMainWindow)
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
    //表格显示
    mShopTable = new Shop_Table(ui->tableWidget,ui->StartDateEdit,
                                ui->FinishDateEdit,ui->FilterButton,
                                ui->ResetButton,ui->ExportButton,
                                mCCMIS,ui->TotalProfit);
    //表格控件信号槽实现
    connect(mShopTable->mStart_Edit,&QDateEdit::dateChanged,
            mShopTable,&Shop_Table::on_Start_Date_Changed);
    connect(mShopTable->mFinish_Edit,&QDateEdit::dateChanged,
            mShopTable,&Shop_Table::on_Finish_Date_Changed);
    connect(mShopTable->mFilter_Btn,&QPushButton::clicked,
            mShopTable,&Shop_Table::on_Filter_clicked);
    connect(mShopTable->mReset_Btn,&QPushButton::clicked,
            mShopTable,&Shop_Table::on_Reset_clicked);
    connect(mShopTable->mExport_Btn,&QPushButton::pressed,
            mShopTable,&Shop_Table::on_Export_pressed);


}

PlaceMainWindow::~PlaceMainWindow()
{
    delete ui;
}

void PlaceMainWindow::time_dispose()
{
    ui->Time->display(AboutUI::ShowDateTime());
}

void PlaceMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}
