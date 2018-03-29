#ifndef USERRECHARGEWINDOW_H
#define USERRECHARGEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>

#include "ccmis.h"
#include "usermainwindow.h"

namespace Ui {
class UserRechargeWindow;
}

class UserRechargeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserRechargeWindow(CCMIS* c, QWidget *parent = 0);  
    void refreshUi();
    ~UserRechargeWindow();

private slots:
    void time_dispose();
    void on_BackButton_clicked();
    void on_WorkButton_clicked();

private:
    Ui::UserRechargeWindow *ui;
    CCMIS* mCCMIS;
};

#endif // USERRECHARGEWINDOW_H
