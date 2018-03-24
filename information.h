#ifndef INFORMATION_H
#define INFORMATION_H


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

static void CopyOneInfo(const Information* src,Information* dst)
    {
        dst->year  =src->year;
        dst->month = src->month;
        dst->day   = src->day;
        dst->hour  = src->hour;
        dst->minute = src->minute;
        dst->second =src->second;
        dst->Inumber = src->Inumber;
        dst->Onumber = src->Onumber;
        dst->tag = src->tag;
        dst->money = src->money;
        dst->next = NULL;
        return;
    }


};

#endif // INFORMATION_H
