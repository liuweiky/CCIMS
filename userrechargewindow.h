#ifndef USERRECHARGEWINDOW_H
#define USERRECHARGEWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "ccmis.h"
#include "aboutui.h"
#include "usermainwindow.h"

namespace Ui {
class UserRechargeWindow;
}

class UserRechargeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserRechargeWindow(CCMIS* c, QWidget *parent = 0);  
    ~UserRechargeWindow();
    void refreshUi();   //基本信息刷新展示

private slots:
    void time_dispose();
    void on_BackButton_clicked();
    void on_WorkButton_clicked();

private:
    Ui::UserRechargeWindow *ui;
    CCMIS* mCCMIS;
};

#endif // USERRECHARGEWINDOW_H
