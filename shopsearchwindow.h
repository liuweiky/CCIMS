#ifndef SHOPSEARCHWINDOW_H
#define SHOPSEARCHWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

namespace Ui {
class ShopSearchWindow;
}

class ShopSearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopSearchWindow(QWidget *parent = 0);
    ~ShopSearchWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);

private slots:
    void on_BackButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::ShopSearchWindow *ui;
};

#endif // SHOPSEARCHWINDOW_H
