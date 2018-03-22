#ifndef CCMIS_H
#define CCMIS_H

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <time.h>
#include <QString>

using namespace std;
#include "information.h"
#include "shop.h"
#include "user.h"
#include "jsonxx.h"



class CCMIS
{

private:
    Information*    mInfo;//信息表头结点
    Shop*   mShop;        //商店表头结点
    User*   mUser;        //用户表头结点
    int mUserNumber;    //当前登陆用户的用户号

    unsigned int totalUserCount;    //用户数统计 下同
    unsigned int totalShopCount;
    unsigned int totalInfoCount;

public:

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

    CCMIS();
    ~CCMIS() {}

    bool ReadInf(string filename);          //读入整个信息表文件
    bool WriteInf(string filename);         //写出整个信息表文件
    void ClearInf();                        //清空整个信息表
    void InsertInf(Information* tempinf);      //添加单个信息表
    void DeleteInf(Information* tempinf);   //删除单个信息表
    void ChangeInf(Information* beforeinf, Information* afterinf);//改变单个信息表

    bool WriteUser(string filename);

    bool ReadShop(string filename);     //读入整个商户表文件
    bool ReadUser(string filename);     //读入整个用户表文件

    void SearchNumber(int id);      //根据卡号输出信息
    void SearchSubsidy(int id);     //根据补贴输出信息
    void SearchTime(int startdate, int startime,
                    int finishdate, int finishtime);  //根据时间输出信息

    int GetTotalCanteenConsumptionByDay(int year, int month, int day,int num); //获取当日食堂消费额
    int GetTotalCanteenAndMarketConsumptionByDay(int year, int month, int day,int num);     //获取当日食堂超市消费额


    User* GetUserByNum(int num);    //通过卡号获取用户指针
    Shop* GetShopByNum(int num);    //通过卡号获取商户指针

    int NewTransaction(int onum, int inum, int mon);   //新建消费交易记录，先减少onum的余额，增加inum的余额（可选），并生成流水号、info，插入到表，更新user.json、info.json，返回是否交易成功，money要乘以100
    bool NewRefund(Information* tempinf);   //撤销某条交易信息
    int NewSubsidy(User* u);  //新建补贴交易
    bool NewRecharge(int num, int money);   //新建充值记录

    string GenerateTag(int onum, int inum, int mon);    //根据当前时间生成流水号，money要乘以100
    string GenerateTag(int year, int month, int day, int hour, int min, int sec, int onum, int inum, int mon);    //手动生成流水号，money要乘以100

    Information* BuildInfo(int onum, int inum, int mon);    //money要乘以100
    Information* BuildInfo(int year, int month, int day, int hour, int min, int sec, int onum, int inum, int mon);

    Information* GetInfoPointer();

    unsigned int GetTotalInfoNumber();
    unsigned int GetTotalUserNumber();
    unsigned int GetTotalShopNumber();



    bool CheckPassword(string password);

    void SetUserNumber(int n);
    int GetUserNum();
};

#endif // CCMIS_H
