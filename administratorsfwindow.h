#ifndef ADMINISTRATORSFWINDOW_H
#define ADMINISTRATORSFWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdministratorSFWindow;
}

class AdministratorSFWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorSFWindow(QWidget *parent = 0);
    ~AdministratorSFWindow();

private:
    Ui::AdministratorSFWindow *ui;
};

#endif // ADMINISTRATORSFWINDOW_H
