 #ifndef USERSEARCHWINDOW_H
#define USERSEARCHWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "ccims.h"
#include "aboutui.h"
#include "table_funcs.h"

namespace Ui {
class UserSearchWindow;
}

class UserSearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserSearchWindow(CCIMS* c, QWidget *parent = 0);
    ~UserSearchWindow();

private slots:
    void time_dispose();
    void on_BackButton_clicked();

private:
    Ui::UserSearchWindow *ui;
    CCIMS* mCCIMS;
    User_Table* mUserTable;
};

#endif // USERSEARCHWINDOW_H
