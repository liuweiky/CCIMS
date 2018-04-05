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
    void on_checkForCurTime_stateChanged(int arg1); //选择当前时间
    void on_dateEdit_dateChanged(const QDate &date);
    void on_timeEdit_2_timeChanged(const QTime &time);

private:
    Ui::AdministratorAddDialog *ui;
    CCMIS* mCCMIS;
    int isModify;
    QDate* mDate;
    QTime* mTime;
};

#endif // ADMINISTRATORADDDIALOG_H
