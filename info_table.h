#ifndef INFO_TABLE_H
#define INFO_TABLE_H
#include <QTableWidgetItem>
#include <QWidget>
#include <QTableWidget>
#include "ccmis.h"
#include <QButtonGroup>
#include <QCheckBox>
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
private:
    Ui::Info_Table *ui;
    CCMIS* mCCMIS;
    QButtonGroup *BtnForSubsidy;
    QCheckBox* CheckForSubsidy;


public slots:
    void onRadionClickedBtn();
    void on_Check_Button_StateChoose(int state);
private slots:
    void on_radioButton_pressed();
};

#endif // INFO_TABLE_H
