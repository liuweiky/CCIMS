#ifndef PLACEMAINWINDOW_H
#define PLACEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlaceMainWindow;
}

class PlaceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaceMainWindow(QWidget *parent = 0);
    ~PlaceMainWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);
    void ShowMoneySlot(double);

private slots:
    void on_BackButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::PlaceMainWindow *ui;
};

#endif // PLACEMAINWINDOW_H
