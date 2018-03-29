#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
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
    explicit UserMainWindow(CCMIS* c, QWidget *parent = 0);
    QString str2qstr(const string str); //处理中文乱码
    string qstr2str(const QString qstr);
    void refreshUi();
    ~UserMainWindow();

private slots:
    void time_dispose();
    void on_BackButton_clicked();
    void on_SearchButton_clicked();
    void on_WorkButton_clicked();

private:
    Ui::UserMainWindow *ui;
    CCMIS* mCCMIS;
};

#endif // USERMAINWINDOW_H
