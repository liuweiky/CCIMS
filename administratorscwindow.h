#ifndef ADMINISTRATORSCWINDOW_H
#define ADMINISTRATORSCWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

namespace Ui {
class AdministratorSCWindow;
}

class AdministratorSCWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorSCWindow(QWidget *parent = 0);
    ~AdministratorSCWindow();

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
    Ui::AdministratorSCWindow *ui;
};

#endif // ADMINISTRATORSCWINDOW_H
