#ifndef ABOUTUI_H
#define ABOUTUI_H

#include <QString>
#include <QDateTime>
#include <QCoreApplication> //读取路径
#include <QCloseEvent>      //窗口关闭
#include <QProgressDialog>

#include "ccmis.h"

class AboutUI
{
public:
    AboutUI();

    static QString ShowDateTime();                  //输出当前日期时间
    //static void CloseTxt(QCloseEvent *event);   //关闭窗口弹窗
    static bool PDlg (QProgressDialog*,
                      CCMIS*,unsigned int);   //进度条显示
};

#endif // ABOUTUI_H
