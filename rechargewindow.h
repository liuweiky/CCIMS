#ifndef RECHARGEWINDOW_H
#define RECHARGEWINDOW_H

#include <QMainWindow>
#include "ccmis.h"
#include <QMessageBox>

namespace Ui {
class RechargeWindow;
}

class RechargeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RechargeWindow(CCMIS* c, QWidget *parent = 0);
    ~RechargeWindow();

private slots:
    void on_rechargeButton_clicked();

private:
    Ui::RechargeWindow *ui;
    CCMIS* mCCMIS;
};

#endif // RECHARGEWINDOW_H
