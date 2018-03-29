#ifndef CCMIS_H
#define CCMIS_H

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <string>

#include <QString>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QtGlobal>         //判断平台
#include <QCoreApplication> //读取路径

using namespace std;

#include "information.h"
#include "shop.h"
#include "user.h"
#include "jsonxx.h"
#include "common_funcs.h"



class CCMIS
{

private:
    Information*    mInfo;  //信息表头结点
    Shop*           mShop;  //商店表头结点
    User*           mUser;  //用户表头结点
    int mUserNumber;        //当前登陆用户的用户号

    //总数统计
    unsigned int totalUserCount;
    unsigned int totalShopCount;
    unsigned int totalInfoCount;

    //数据链表导出为json
    jsonxx::Array LinkListToJson(User* user_list);
    jsonxx::Array LinkListToJson(Information* info_list);
    jsonxx::Array LinkListToJson(Shop* shop_list);

    //json导出到文件
    bool SaveJsonArrToFile(const jsonxx::Array& ToSaveJson,string filename);

    //判断前项时间是否小于后项
    bool TimeBool(Information* beforetime, Information* aftertime);

public:
    //跨平台判断
    static const unsigned int PLATFORM_JUDGE;

    //自定义常量
    static const string BACKBUTTON_PICTURE_NAME;

    static const string OUT_FILE_NAME;
    static const string USER_FILE_NAME;
    static const string SHOP_FILE_NAME;
    static const string INFO_FILE_NAME;

    static const string JSON_KEY_NUMBER;
    static const string JSON_KEY_NAME;
    static const string JSON_KEY_PASSWORD;
    static const string JSON_KEY_BALANCE;
    static const string JSON_KEY_COUPON;

    static const string JSON_KEY_TAG;
    static const string JSON_KEY_YEAR;
    static const string JSON_KEY_MONTH;
    static const string JSON_KEY_DAY;
    static const string JSON_KEY_HOUR;
    static const string JSON_KEY_MINUTE;
    static const string JSON_KEY_SECOND;
    static const string JSON_KEY_ONUMBER;
    static const string JSON_KEY_INUMBER;
    static const string JSON_KEY_MONEY;

    static const int SUPERUSER_BEGIN;
    static const int SUPERUSER_END;
    static const int SHOP_CANTEEN_BEGIN;
    static const int SHOP_CANTEEN_END;
    static const int SHOP_MARKET_BEGIN;
    static const int SHOP_MARKET_END;
    static const int SHOP_BATH_BEGIN;
    static const int SHOP_BATH_END;
    static const int SHOP_BEGIN;
    static const int SHOP_END;
    static const int USER_TEA_EMP_BEGIN;
    static const int USER_TEA_EMP_END;
    static const int USER_BEGIN;
    static const int USER_END;

    static const int MESSAGE_TRANSACTION_SUCCESS;
    static const int MESSAGE_TRANSACTION_NO_USER;
    static const int MESSAGE_TRANSACTION_NO_SHOP;
    static const int MESSAGE_TRANSACTION_OVERFLOW;
    static const int MESSAGE_TRANSACTION_BALANCE_NOT_ENOUGH;
    static const int MESSAGE_TRANSACTION_MONEY_LOWER_THAN_ZERO;
    static const int MESSAGE_TRANSACTION_UNKNOWN;

    static const int GROUP_SUPERUSER;
    static const int GROUP_CANTEEN;
    static const int GROUP_MARKET;
    static const int GROUP_BATH;

    static const int THREAD_TYPE_W_USER;
    static const int THREAD_TYPE_W_INFO;
    static const int THREAD_TYPE_W_SHOP;

    static const int THREAD_TYPE_R_USER;
    static const int THREAD_TYPE_R_INFO;
    static const int THREAD_TYPE_R_SHOP;

    CCMIS();
    ~CCMIS() {}

    //传文件线程
    class JsonThread: public QThread
    {
    public:
        virtual void run()
        {
            switch (type) {
            case -1:
                mCCMIS->ReadInf(mCCMIS->INFO_FILE_NAME);
                break;
            case -2:
                mCCMIS->ReadShop(mCCMIS->SHOP_FILE_NAME);
                break;
            case -3:
                mCCMIS->ReadUser(mCCMIS->USER_FILE_NAME);
                break;
            case 1:
                mCCMIS->WriteInf(mCCMIS->INFO_FILE_NAME);
                break;
            case 2:

                break;
            case 3:
                mCCMIS->WriteUser(mCCMIS->USER_FILE_NAME);
                break;
            default:
                break;
            }
        }
        JsonThread(CCMIS* c, int t): mCCMIS(c), type(t){}

    private:
        int type;
        CCMIS* mCCMIS;
    };

    QString FilenameCorrect(string filename);       //应对不同平台输出文件路径
    string ReadAllFileToQString(string filename);   //读取文件至std::string

    //写入文件的话，默认一个参数是私有成员变量链表 写进文件
    //注意！默认参数不允许是类内成员变量，原因是编译期无法确定内容，只有静态变量可以当默认参数
    bool ReadInf(string filename);                          //读入整个信息表文件
    //下面这个函数强行调用了写好的函数，导致没法判断原文件流水号是否正确！ by陆子旭
    unsigned int ImportInf(string filename);                //添加信息表文件信息（返回成功数）
    bool WriteInf(string filename);                         //写出minfo表文件
    bool WriteInf(string filename, Information *info_list); //写出指定信息表文件
    bool ReadUser(string filename);                         //下同
    bool WriteUser(string filename);
    bool WriteUser(string filename, User *user_list);
    bool ReadShop(string filename);
    bool WriteShop(string filename);
    bool WriteShop(string filename, Shop *shop_list);

    void WriteInfForDel();

    void ClearInf();                                                //清空整个信息表
    void InsertInf(Information* tempinf);                           //添加单个信息表
    void DeleteInf(Information* tempinf);                           //删除单个信息表
    void ChangeInf(Information* beforeinf, Information* afterinf);  //改变单个信息表

    int GetTotalCanteenConsumptionByDay
    (int year, int month, int day,int num);     //获取当日食堂消费额
    int GetTotalCanteenAndMarketConsumptionByDay
    (int year, int month, int day,int num);     //获取当日食堂超市消费额

    User*   GetUserByNum(int num);          //通过卡号获取用户指针
    Shop*   GetShopByNum(int num);          //通过卡号获取商户指针
    QString GetAllNameByNum(int num);       //通过卡号得到用户名？
        int GetUserNum();                   //获取当前用户流水号
    QString GetCurrentUserName();           //获取当前用户名
    User*   GetCurrentUser();               //获取当前用户结点
    Shop*   GetCurrentShop();               //获取当前商店结点


    //新建消费交易记录，先减少onum的余额，增加inum的余额（可选），
    //并生成流水号、info，插入到表，更新user.json、info.json，
    //返回是否交易成功，money要乘以100
    //加了时间，不需要默认-1 by陆子旭
    int NewTransaction(int onum, int inum, int mon,
                       int year = -1, int month= -1, int day= -1,
                       int hour= -1, int min= -1, int sec= -1);
    bool NewRefund(Information* tempinf);   //撤销某条交易信息
    int NewSubsidy(User* u);                //新建补贴交易
    bool NewRecharge(int num, int money);   //新建充值记录

    //根据当前时间生成流水号，money要乘以100
    string GenerateTag(int onum, int inum, int mon);
    //手动生成流水号，money要乘以100
    string GenerateTag(int year, int month, int day, int hour,
                       int min, int sec, int onum, int inum, int mon);

    //money要乘以100
    Information* BuildInfo(int onum, int inum, int mon,
                           int year = -1, int month= -1, int day= -1,
                           int hour= -1, int min= -1, int sec= -1);

    Information* GetInfoPointer();

    unsigned int GetTotalInfoNumber();
    unsigned int GetTotalUserNumber();
    unsigned int GetTotalShopNumber();


    void SearchNumber(int id);                          //根据卡号输出信息
    void SearchTime(int startdate, int startime,
                    int finishdate, int finishtime);    //根据时间输出信息

    Information* GetInfoByTag(QString tag);

    //默认返回所有补贴信息
    Information* SearchInfoByInum
    (int inum = 0, unsigned long start_date_num = 0,
     unsigned int start_time_num = 0 ,
     unsigned long finish_date_num = 99999999,
     unsigned int finish_time_num = 9999 );

    Information* SearchInfoByOnum
    (int onum = 2, unsigned long start_date_num = 0,
     unsigned int start_time_num = 0 ,
     unsigned long finish_date_num = 99999999,
     unsigned int finish_time_num = 9999 );

    bool CheckPassword(string password);

    void SetUserNumber(int n);

    QString ShowDateTime();     //输出当前日期时间
    void CouponFresh();         //月初刷新劵额
};

#endif // CCMIS_H
