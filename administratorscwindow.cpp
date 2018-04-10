#include "administratorscwindow.h"
#include "ui_administratorscwindow.h"

AdministratorSCWindow::AdministratorSCWindow(CCIMS *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorSCWindow)
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

    //表格显示
    mAdminTable = new Admin_Table(ui->tableWidget,ui->StartDateEdit,
                                  ui->FinishDateEdit,ui->FilterButton,
                                  ui->resetButton,ui->ExportButton,mCCIMS,
                                  ui->DeleteButton,ui->InsertButton,
                                  ui->AlterButton,ui->CheckForSubsidy);

    //表格控件信号槽实现
    connect(mAdminTable->mStart_Edit,&QDateEdit::dateChanged,
            mAdminTable,&Admin_Table::on_Start_Date_Changed);

    connect(mAdminTable->mFinish_Edit,&QDateEdit::dateChanged,
            mAdminTable,&Admin_Table::on_Finish_Date_Changed);

    connect(mAdminTable->mFilter_Btn,&QPushButton::clicked,
            mAdminTable,&Admin_Table::on_Filter_clicked);

    connect(mAdminTable->mReset_Btn,&QPushButton::clicked,
            mAdminTable,&Admin_Table::on_Reset_clicked);

    connect(mAdminTable->mExport_Btn,&QPushButton::pressed,
            mAdminTable,&Admin_Table::on_Export_pressed);

    connect(mAdminTable->mSubsidy_Chck,&QCheckBox::stateChanged,
            mAdminTable,&Admin_Table::on_Subsidy_Check_Admin);

    connect(mAdminTable->mDelete_Btn,&QCheckBox::clicked,
            mAdminTable,&Admin_Table::on_DeleteButton_clicked);

    connect(mAdminTable->mTable,&QTableWidget::itemPressed,
            mAdminTable,&Admin_Table::on_tableWidget_itemClicked);
}

AdministratorSCWindow::~AdministratorSCWindow()
{
    delete ui;
}

void AdministratorSCWindow::UpdateItem()
{
    mAdminTable->mTable->setRowCount(0);
    mAdminTable->mTable->clear();
    mAdminTable->init_Table_Header();
}

Admin_Table* AdministratorSCWindow::GetTable()
{
    return mAdminTable;
}

void AdministratorSCWindow::time_dispose()
{
    ui->Time->display(AboutUI::ShowDateTime());
}

void AdministratorSCWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void AdministratorSCWindow::on_InsertButton_clicked()
{
    AdministratorAddDialog* aad = new AdministratorAddDialog(mCCIMS, false, this);
    aad->setInOutNumEnable(false);
    aad->setGeometry(this->x()+this->width()/4,this->y()+this->height()/4,
                     this->width(),this->height());
    aad->show();
}

void AdministratorSCWindow::on_AlterButton_clicked()
{
    if (mAdminTable->mCurrentItemIndex >= 0)
    {
        AdministratorAddDialog* aad = new AdministratorAddDialog(mCCIMS, 1, this);
        aad->setInOutNumEnable(true);

        aad->setGeometry(this->x()+this->width()/4,this->y()+this->height()/4,
                this->width(),this->height());
        aad->show();
    }
}
