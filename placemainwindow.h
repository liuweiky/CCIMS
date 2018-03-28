#ifndef PLACEMAINWINDOW_H
#define PLACEMAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

#include "ccmis.h"

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
    void showtime();
    void on_BackButton_clicked();

private:
    Ui::PlaceMainWindow *ui;
    CCMIS* mCCMIS;
};

#endif // PLACEMAINWINDOW_H
