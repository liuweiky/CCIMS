#ifndef USERSEARCHWINDOW_H
#define USERSEARCHWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserSearchWindow;
}

class UserSearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserSearchWindow(QWidget *parent = 0);
    ~UserSearchWindow();

private:
    Ui::UserSearchWindow *ui;
};

#endif // USERSEARCHWINDOW_H
