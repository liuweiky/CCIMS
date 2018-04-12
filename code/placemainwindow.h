#ifndef PLACEMAINWINDOW_H
#define PLACEMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "ccims.h"
#include "aboutui.h"
#include "table_funcs.h"
namespace Ui {
class PlaceMainWindow;
}

class PlaceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaceMainWindow(CCIMS* c, QWidget *parent = 0);
    ~PlaceMainWindow();

private slots:
    void time_dispose();
    void on_BackButton_clicked();

private:
    Ui::PlaceMainWindow *ui;
    CCIMS* mCCIMS;
    ShopPlace_Table* mShopPlaceTable;
};

#endif // PLACEMAINWINDOW_H
