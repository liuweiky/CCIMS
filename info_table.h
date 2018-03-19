#ifndef INFO_TABLE_H
#define INFO_TABLE_H
#include <QTableWidgetItem>
#include <QWidget>
#include "information.h"
namespace Ui {
class Info_Table;
}

class Info_Table : public QWidget
{
    Q_OBJECT

public:
    explicit Info_Table(Information* ALL_INFO,QWidget *parent = 0);
    ~Info_Table();
    void PrintOneInfo(Information* OneLineInfo,int  IndexOfRow);

private:
    Ui::Info_Table *ui;
};

#endif // INFO_TABLE_H
