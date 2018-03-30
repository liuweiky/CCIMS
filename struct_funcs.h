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
    
    static QString InfoToMoneyStr(Information* one_info);
    static QDateTime InfoToDateTime(Information* one_info);
    static void CopyOneInfo(const Information* src,Information* dst);
    

};

struct Shop
{
    int         number;
    QString     name;
    std::string password;
    Shop*       next;       //下个结点
};

struct User
{
    int         number;
    QString     name;
    std::string password;
    int         balance;    //余额
    int         coupon;     //劵
    User*       next;       //下个结点
};







#endif // STRUCT_FUNCS_H
