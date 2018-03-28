#ifndef SHOPSERVICEWINDOW_H
#define SHOPSERVICEWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QMessageBox>

#include "ccmis.h"

namespace Ui {
class ShopServiceWindow;
}

class ShopServiceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopServiceWindow(CCMIS* c, QWidget *parent = 0);
    ~ShopServiceWindow();

private slots:
    void showtime();
    void on_BackButton_clicked();
    void on_WorkButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);

private:
    Ui::ShopServiceWindow *ui;
    CCMIS* mCCMIS;
};

#endif // SHOPSERVICEWINDOW_H
