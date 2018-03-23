#ifndef ADMINISTRATORLEADWINDOW_H
#define ADMINISTRATORLEADWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

namespace Ui {
class AdministratorLeadWindow;
}

class AdministratorLeadWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorLeadWindow(QWidget *parent = 0);
    ~AdministratorLeadWindow();

public slots:
    void showtime();

private slots:
    //重新显示主界面：X，Y，宽，长
    void on_BackButton_clicked();
    void on_WorkButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);

private:
    Ui::AdministratorLeadWindow *ui;
};

#endif // ADMINISTRATORLEADWINDOW_H
