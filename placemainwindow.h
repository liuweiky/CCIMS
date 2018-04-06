#ifndef PLACEMAINWINDOW_H
#define PLACEMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "ccmis.h"
#include "aboutui.h"
#include "table_funcs.h"
namespace Ui {
class PlaceMainWindow;
}

class PlaceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaceMainWindow(CCMIS* c, QWidget *parent = 0);
    ~PlaceMainWindow();

private slots:
    void time_dispose();
    void on_BackButton_clicked();

private:
    Ui::PlaceMainWindow *ui;
    CCMIS* mCCMIS;
    Shop_Table* mShopTable;
};

#endif // PLACEMAINWINDOW_H
