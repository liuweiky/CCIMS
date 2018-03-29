#ifndef INFORMATION_H
#define INFORMATION_H

#include <QDateTime>
#include <QDate>
#include <QTime>
#include <string>
#include <QString>

struct Information
{
    std::string  tag;       //流水号
    unsigned int year;      //年
    unsigned int month;     //月
    unsigned int day;       //日
    unsigned int hour;      //时
    unsigned int minute;    //分
    unsigned int second;    //秒
    unsigned int Onumber;   //出账卡号
    unsigned int Inumber;   //收账卡号
    unsigned int money;     //交易额
    Information* next;      //下个结点

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






static QString InfoToDateStr(Information* one_info)
{
    QString year=QString::number(one_info->year);
    QString month =QString::number(one_info->month).sprintf("%02d",one_info->month);
    QString day =QString::number(one_info->day).sprintf("%02d",one_info->day);
    return QString(year + " - " + month + " - "+ day);
}

static  QString InfoToTimeStr(Information* one_info)
{
    QString hour =QString::number(one_info->hour).sprintf("%02d",one_info->hour);
    QString min = QString::number(one_info->minute).sprintf("%02d",one_info->minute);
    QString sec = QString::number(one_info->second).sprintf("%02d",one_info->second);
    return QString(hour + ":" + min + ":" + sec);
}

static QString InfoToMoneyStr(Information* one_info)
{
    unsigned int MoneyInt,MoneyFloat;
    MoneyFloat = (one_info->money)%100;
    MoneyInt =   (one_info->money)/100;
    return QString(QString::number(MoneyInt) + "." +
                   QString::number(MoneyFloat).sprintf("%02d",MoneyFloat));
}

};
#endif // INFORMATION_H
