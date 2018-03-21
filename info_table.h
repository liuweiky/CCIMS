#ifndef INFO_TABLE_H
#define INFO_TABLE_H
#include <QTableWidgetItem>
#include <QWidget>

#include "ccmis.h"
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

    QString GetNameByNum(CCMIS* ccmis_system,int num);

private:
    Ui::Info_Table *ui;
};

#endif // INFO_TABLE_H
