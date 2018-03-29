#ifndef ADMINISTRATORMAINWINDOW_H
#define ADMINISTRATORMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "administratorleadwindow.h"
#include "administratorscwindow.h"

#include "ccmis.h"

namespace Ui {
class AdministratorMainWindow;
}

class AdministratorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorMainWindow(CCMIS* c, QWidget *parent = 0);
    ~AdministratorMainWindow();

private slots:
    void time_dispose();
    void on_BackButton_clicked();
    void on_ImportButton_clicked();
    void on_WorkButton_clicked();

private:
    Ui::AdministratorMainWindow *ui;
    CCMIS* mCCMIS;
};

#endif // ADMINISTRATORMAINWINDOW_H
