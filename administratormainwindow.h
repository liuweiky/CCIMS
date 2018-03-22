#ifndef ADMINISTRATORMAINWINDOW_H
#define ADMINISTRATORMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdministratorMainWindow;
}

class AdministratorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorMainWindow(QWidget *parent = 0);
    ~AdministratorMainWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);

private slots:
    //重新显示主界面：X，Y，宽，长
    void reshow(int,int,int,int);
    void on_BackButton_clicked();
    void on_SearchButton_clicked();
    void on_WorkButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);
    void ShowMoneySignal(double);

private:
    Ui::AdministratorMainWindow *ui;
};

#endif // ADMINISTRATORMAINWINDOW_H
