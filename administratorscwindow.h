#ifndef ADMINISTRATORSCWINDOW_H
#define ADMINISTRATORSCWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "ccmis.h"

namespace Ui {
class AdministratorSCWindow;
}

class AdministratorSCWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorSCWindow(CCMIS* c, QWidget *parent = 0);
    ~AdministratorSCWindow();

private slots:
    void time_dispose();
    void on_BackButton_clicked();

private:
    Ui::AdministratorSCWindow *ui;
    CCMIS *mCCMIS;
};

#endif // ADMINISTRATORSCWINDOW_H
