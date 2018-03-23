#ifndef USERRECHARGEWINDOW_H
#define USERRECHARGEWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QMessageBox>

#include "ccmis.h"

namespace Ui {
class UserRechargeWindow;
}

class UserRechargeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserRechargeWindow(CCMIS* c, QWidget *parent = 0);
    ~UserRechargeWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);
    void ShowMoneySlot(double);
    void ShowCouponSlot(double);

private slots:
    //重新显示主界面：X，Y，宽，长
    void on_BackButton_clicked();
    void on_WorkButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);

private:
    Ui::UserRechargeWindow *ui;
    CCMIS* mCCMIS;
};

#endif // USERRECHARGEWINDOW_H
