#ifndef USERSFWINDOW_H
#define USERSFWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserSFWindow;
}

class UserSFWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserSFWindow(QWidget *parent = 0);
    ~UserSFWindow();

private:
    Ui::UserSFWindow *ui;
};

#endif // USERSFWINDOW_H
