#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
#include "ccmis.h"
#include "rechargewindow.h"

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(CCMIS* c, QWidget *parent = 0);
    QString str2qstr(const string str); //处理中文乱码
    string qstr2str(const QString qstr);
    ~UserMainWindow();

private slots:
    void on_rechargeButton_clicked();

private:
    Ui::UserMainWindow *ui;
    CCMIS* mCCMIS;
};

#endif // USERMAINWINDOW_H
