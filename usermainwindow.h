#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QWidget>

namespace Ui {
class usermainwindow;
}

class usermainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit usermainwindow(QWidget *parent = 0);
    ~usermainwindow();

private:
    Ui::usermainwindow *ui;
};

#endif // USERMAINWINDOW_H
