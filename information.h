#ifndef INFORMATION_H
#define INFORMATION_H

#include <string>

struct Information
{
    string tag; //流水号
    unsigned int year;   //日期
    unsigned int month;   //日期
    unsigned int day;   //日期
    unsigned int hour;   //日期
    unsigned int minute;   //日期
    unsigned int Onumber;//出账卡号
    unsigned int Inumber;//收账卡号
    unsigned int money;  //交易额
    Information* next;//下个结点
};

#endif // INFORMATION_H
