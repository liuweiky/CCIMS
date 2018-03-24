 #ifndef USERSEARCHWINDOW_H
#define USERSEARCHWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

namespace Ui {
class UserSearchWindow;
}

class UserSearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserSearchWindow(QWidget *parent = 0);
    ~UserSearchWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);
    void ShowMoneySlot(double);
    void ShowCouponSlot(double);

private slots:
    void on_BackButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::UserSearchWindow *ui;
};

#endif // USERSEARCHWINDOW_H
