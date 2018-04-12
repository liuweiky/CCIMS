#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "usersearchwindow.h"
#include "userrechargewindow.h"

#include "ccims.h"
#include "aboutui.h"

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(CCIMS* c, QWidget *parent = 0);
    ~UserMainWindow();
    QString str2qstr(const string str); //处理中文乱码
    string qstr2str(const QString qstr);
    void refreshUi();   //基本信息刷新展示

private slots:
    void time_dispose();
    void on_BackButton_clicked();
    void on_SearchButton_clicked();
    void on_WorkButton_clicked();

private:
    Ui::UserMainWindow *ui;
    CCIMS* mCCIMS;
};

#endif // USERMAINWINDOW_H
