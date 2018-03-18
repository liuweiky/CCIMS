#ifndef SUPERUSERMAINWINDOW_H
#define SUPERUSERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SuperuserMainWindow;
}

class SuperuserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SuperuserMainWindow(QWidget *parent = 0);
    ~SuperuserMainWindow();

private:
    Ui::SuperuserMainWindow *ui;
};

#endif // SUPERUSERMAINWINDOW_H
