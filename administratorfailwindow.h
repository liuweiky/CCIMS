#ifndef ADMINISTRATORFAILWINDOW_H
#define ADMINISTRATORFAILWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdministratorFailWindow;
}

class AdministratorFailWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorFailWindow(QWidget *parent = 0);
    ~AdministratorFailWindow();

private:
    Ui::AdministratorFailWindow *ui;
};

#endif // ADMINISTRATORFAILWINDOW_H
