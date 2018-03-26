#ifndef INFO_TABLE_H
#define INFO_TABLE_H
#include <QTableWidgetItem>
#include <QWidget>
#include <QTableWidget>
#include "ccmis.h"
#include <QButtonGroup>
#include <QCheckBox>
#include "information.h"
#include <QDateTimeEdit>
namespace Ui {
class Info_Table;
}

class Info_Table : public QWidget
{
    Q_OBJECT

public:
    explicit Info_Table(CCMIS* ccmis_system,QWidget *parent = 0);
    ~Info_Table();
    void PrintOneInfo(CCMIS* ccmis_system, Information* OneLineInfo,int  IndexOfRow);

    //只显示一个人的补助表格
    void GetWholeOneUserSubsidyTable(QTableWidget* qtable,int inum);

    //同一个入帐账号 表格
    void GetWholeOneUserSearchTable(QTableWidget* qtable,int onum);
    void ShowSameOnumOneInfo(QTableWidget *qtable,Information* one_info,int& row_index);



    //同一个出账账号 表格
    void ShowSameInumOneInfo(QTableWidget *qtable,Information* one_info, int &row_index);
     void GetWholeOneShopSearchTable(QTableWidget* qtable, int inum);


     //日期控件 设置
     void SetStartFinishRange(QDateTimeEdit* start_edit,QDateTimeEdit* finish_edit);

private:
    Ui::Info_Table *ui;
    CCMIS* mCCMIS;

    QCheckBox* CheckForSubsidy;
    QDateTimeEdit* Start_Date_Time_Edit;
    QDateTimeEdit* Finish_Date_Time_Edit;
public:
    QDateTime* Start_Date_Time;
    QDateTime* Finish_Date_Time;

public slots:

    void on_Check_Button_StateChoose(int state);
   void onStartDateTimeChanged(const QDateTime &dateTime);
   void onFinishDateTimeChanged(const QDateTime &dateTime);
};

#endif // INFO_TABLE_H
