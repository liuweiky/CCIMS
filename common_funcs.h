#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H


#include <QString>
#include <QTextCodec>
#include <string>
using std::string;

struct Date
{
    int year;
    int month;
    int day;
    Date (unsigned long NumDate){
        year = NumDate / 10000;
        month = int(NumDate / 100 % 100);
        day = int(NumDate % 100);
    }
    static unsigned long DateToNum(int yr,int mth,int dy){
        return yr*10000 + mth*100+dy;
    }
};

struct Time
{
    int hour;
    int minute;
    int second;
    Time(unsigned long NumTime){
        //时间数字段有两种可能，一种带秒，一种不带秒
        if(NumTime < 9999){
            second = 0;
            minute = NumTime%100;
            hour = int(NumTime/100);
        }else if(NumTime < 999999){
            second = NumTime % 100;
            minute = int(NumTime / 100 % 100);
            hour = int(NumTime / 10000);
        }
    }

    static unsigned int TimeToNum(int hr,int min,int sec = 0){
        return hr*10000 + min * 100 + sec;
    }
};

class COMMON_FUNCS
{
public:




    // QString(Unicode) -> std::string (UTF8)
    static string ToUTF8String(const QString& qstr)
    {
//        QByteArray arr = qstr.toUtf8();
//        string cstr = arr.data();
//        return cstr;
        return string((const char *)qstr.toLocal8Bit());
    }

    // std::string (UTF8) -> QString(Unicode)
    static QString UTF8ToQString(const string& cstr)
    {
        QString qstr = QString::fromUtf8(cstr.c_str(), cstr.length());
        return qstr;
    }

    // QString(Unicode) -> std::string (GBK)
   static string ToGBKString(const QString& qstr)
   {
       QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
       if(!pCodec) return "";

       QByteArray arr = pCodec->fromUnicode(qstr);
       string cstr = arr.data();
       return cstr;
   }

   // std::string (GBK) -> QString(Unicode)
   static QString GBKToQString(const string& cstr)
   {
       QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
       if(!pCodec) return "";

       QString qstr = pCodec->toUnicode(cstr.c_str(), cstr.length());
       return qstr;
   }
};

#endif // COMMON_FUNCS_H
