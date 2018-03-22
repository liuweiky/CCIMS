#ifndef INFORMATION_H
#define INFORMATION_H

#include <QString>
#include <string>

struct Information
{
    std::string tag; //流水号
    unsigned int year;   //年
    unsigned int month;   //月
    unsigned int day;   //日
    unsigned int hour;   //时
    unsigned int minute;   //分
    unsigned int second;   //秒
    unsigned int Onumber;//出账卡号
    unsigned int Inumber;//收账卡号
    unsigned int money;  //交易额
    Information* next;//下个结点
};

#endif // INFORMATION_H
