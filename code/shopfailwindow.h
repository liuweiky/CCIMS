#ifndef SHOPFAILWINDOW_H
#define SHOPFAILWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

namespace Ui {
class ShopFailWindow;
}

class ShopFailWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopFailWindow(QWidget *parent = 0);
    ~ShopFailWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::ShopFailWindow *ui;
};

#endif // SHOPFAILWINDOW_H
