#ifndef SHOPSUCCESSWINDOW_H
#define SHOPSUCCESSWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

namespace Ui {
class ShopSuccessWindow;
}

class ShopSuccessWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopSuccessWindow(QWidget *parent = 0);
    ~ShopSuccessWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::ShopSuccessWindow *ui;
};

#endif // SHOPSUCCESSWINDOW_H
