#ifndef SHOPSFWINDOW_H
#define SHOPSFWINDOW_H

#include <QMainWindow>

namespace Ui {
class ShopSFWindow;
}

class ShopSFWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopSFWindow(QWidget *parent = 0);
    ~ShopSFWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::ShopSFWindow *ui;
};

#endif // SHOPSFWINDOW_H
