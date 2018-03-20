#ifndef SHOPMAINWINDOW_H
#define SHOPMAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

namespace Ui {
class ShopMainWindow;
}

class ShopMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopMainWindow(QWidget *parent = 0);
    ~ShopMainWindow();

private slots:
    void on_BackButton_clicked();

    void on_SearchButton_clicked();

public slots:
    void showtime();
    void showname(QString);

signals:
    void BackMainWindow();

private:
    Ui::ShopMainWindow *ui;
};

#endif // SHOPMAINWINDOW_H
