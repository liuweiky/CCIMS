#ifndef USERRECHARGEWINDOW_H
#define USERRECHARGEWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "ccims.h"
#include "aboutui.h"
#include "usermainwindow.h"

namespace Ui {
class UserRechargeWindow;
}

class UserRechargeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserRechargeWindow(CCIMS* c, QWidget *parent = 0);  
    ~UserRechargeWindow();
    void refreshUi();   //基本信息刷新展示

private slots:
    void time_dispose();
    void on_BackButton_clicked();
    void on_WorkButton_clicked();

private:
    Ui::UserRechargeWindow *ui;
    CCIMS* mCCIMS;
};

#endif // USERRECHARGEWINDOW_H
