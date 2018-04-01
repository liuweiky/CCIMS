#ifndef ADMINISTRATORADDDIALOG_H
#define ADMINISTRATORADDDIALOG_H

#include <QDialog>

#include "ccmis.h"
#include "aboutui.h"
#include "administratorscwindow.h"

namespace Ui {
class AdministratorAddDialog;
}

class AdministratorAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdministratorAddDialog(CCMIS* c, int ismod, QWidget *parent = 0);
    ~AdministratorAddDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AdministratorAddDialog *ui;
    CCMIS* mCCMIS;
    int isModify;
};

#endif // ADMINISTRATORADDDIALOG_H
