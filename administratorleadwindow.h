#ifndef ADMINISTRATORLEADWINDOW_H
#define ADMINISTRATORLEADWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdministratorLeadWindow;
}

class AdministratorLeadWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorLeadWindow(QWidget *parent = 0);
    ~AdministratorLeadWindow();

private:
    Ui::AdministratorLeadWindow *ui;
};

#endif // ADMINISTRATORLEADWINDOW_H
