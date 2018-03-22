#ifndef USERRECHARGEWINDOW_H
#define USERRECHARGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserRechargeWindow;
}

class UserRechargeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserRechargeWindow(QWidget *parent = 0);
    ~UserRechargeWindow();

private:
    Ui::UserRechargeWindow *ui;
};

#endif // USERRECHARGEWINDOW_H
