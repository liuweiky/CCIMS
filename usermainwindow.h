#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

#include "usersearchwindow.h"
#include "userrechargewindow.h"

#include "ccmis.h"

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = 0);
    QString str2qstr(const string str); //处理中文乱码
    string qstr2str(const QString qstr);
    ~UserMainWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);
    void ShowMoneySlot(double);
    void ShowCouponSlot(double);

private slots:
    //重新显示主界面：X，Y，宽，长
    void reshow(int,int,int,int);
    void on_BackButton_clicked();
    void on_SearchButton_clicked();
    void on_WorkButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);
    void ShowMoneySignal(double);
    void ShowCouponSignal(double);

private:
    Ui::UserMainWindow *ui;
    CCMIS* mCCMIS;
    UserRechargeWindow mURW;
    UserSearchWindow mUSW;
};

#endif // USERMAINWINDOW_H
