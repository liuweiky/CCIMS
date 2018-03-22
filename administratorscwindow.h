#ifndef ADMINISTRATORSCWINDOW_H
#define ADMINISTRATORSCWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdministratorSCWindow;
}

class AdministratorSCWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorSCWindow(QWidget *parent = 0);
    ~AdministratorSCWindow();

private:
    Ui::AdministratorSCWindow *ui;
};

#endif // ADMINISTRATORSCWINDOW_H
