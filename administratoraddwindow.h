#ifndef ADMINISTRATORADDWINDOW_H
#define ADMINISTRATORADDWINDOW_H

#include <QMainWindow>
#include "ccmis.h"
#include "administratorscwindow.h"

namespace Ui {
class AdministratorAddWindow;
}

class AdministratorAddWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorAddWindow(CCMIS* c, int ismod,QWidget *parent = 0);
    ~AdministratorAddWindow();

private slots:
    void on_AddButton_clicked();

private:
    int isModify;
    Ui::AdministratorAddWindow *ui;
    CCMIS* mCCMIS;
};

#endif // ADMINISTRATORADDWINDOW_H
