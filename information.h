#ifndef INFORMATION_H
#define INFORMATION_H

#include <string>

struct Information
{
    unsigned long  date;   //日期
    unsigned long  time;   //时间
    unsigned int Onumber;//出账卡号
    unsigned int Inumber;//收账卡号
    unsigned int money;  //交易额
    Information* next;//下个结点
};

#endif // INFORMATION_H
