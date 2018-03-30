#include "struct_funcs.h"


static QString InfoToMoneyStr(Information* one_info)
static QDateTime InfoToDateTime(Information* one_info)
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


static QDateTime InfoToDateTime(Information* one_info)
{
    QDate* info_date = new QDate(one_info->year,one_info->month,one_info->day);
    QTime* info_time = new QTime(one_info->hour,one_info->minute,one_info->second);
    return QDateTime((*info_date),(*info_time));
}





static QString InfoToMoneyStr(Information* one_info)
{
    unsigned int MoneyInt,MoneyFloat;
    MoneyFloat = (one_info->money)%100;
    MoneyInt =   (one_info->money)/100;
    return QString(QString::number(MoneyInt) + "." +
                   QString::number(MoneyFloat).sprintf("%02d",MoneyFloat));
}


