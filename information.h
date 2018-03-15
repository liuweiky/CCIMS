#ifndef INFORMATION_H
#define INFORMATION_H

#include <string>

struct Information
{
    int date;   //日期
    int time;   //时间
    int Onumber;//出账卡号
    int Inumber;//收账卡号
    int money;  //交易额
    Information* next;//下个结点
};

#endif // INFORMATION_H
