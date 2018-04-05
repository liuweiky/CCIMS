#ifndef STRUCT_FUNCS_H
#define STRUCT_FUNCS_H

#include <QDateTime>
#include <string>
#include <QString>
#include <jsonxx.h>

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
    
    static void CopyOneInfo(const Information* src,Information* dst);   //复制信息
    static QString InfoToMoneyStr(Information* one_info);   //提取信息日期
    static QDateTime InfoToDateTime(Information* one_info); //提取信息金钱
};

struct Shop
{
    int         number;     //卡号
    QString     name;       //用户名
    std::string password;   //密码
    Shop*       next;       //下个结点
};

struct User
{
    int         number;     //卡号
    QString     name;       //用户名
    std::string password;   //密码
    int         balance;    //余额
    int         coupon;     //劵
    User*       next;       //下个结点
};

#endif // STRUCT_FUNCS_H
