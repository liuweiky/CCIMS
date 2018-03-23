#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H


#include <QString>
#include <QTextCodec>
#include <string>
using std::string;

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
