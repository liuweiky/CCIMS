#ifndef SHOPMAINWINDOW_H
#define SHOPMAINWINDOW_H

#include <QMainWindow>

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

signals:
    void BackMainWindow();

private:
    Ui::ShopMainWindow *ui;
};

#endif // SHOPMAINWINDOW_H
