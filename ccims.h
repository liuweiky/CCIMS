#ifndef CCIMS_H
#define CCIMS_H

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
#include <QCloseEvent>      //窗口关闭

#include "common_funcs.h"
#include "struct_funcs.h"
#include "jsonxx.h"

using namespace std;

class CCIMS
{

private:
    Information*    mInfo;  //信息表头结点
    Shop*           mShop;  //商店表头结点
    User*           mUser;  //用户表头结点
    int mUserNumber;        //当前登陆用户的用户号

    int mReadThreadCount;
    int mWriteThreadCount;

    //总数统计
    unsigned int totalUserCount;
    unsigned int totalShopCount;
    unsigned int totalInfoCount;

    jsonxx::Array LinkListToJson(User* user_list);
    jsonxx::Array LinkListToJson(Information* info_list);
    jsonxx::Array LinkListToJson(Shop* shop_list);
    bool SaveJsonArrToFile(const jsonxx::Array& ToSaveJson,string filename);

public:
    unsigned int GuessTotalNumber; //预计总信息数
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

    CCIMS();
    ~CCIMS() {}

    int GetCurrentReadThreadCount();
    int GetCurrentWriteThreadCount();

    //传文件线程
    class JsonThread: public QThread
    {
    public:
        virtual void run()
        {
            switch (type) {
            case -1:
                qDebug() << "Read info thread start.";
                mCCIMS->mReadThreadCount += 1;
                mCCIMS->ReadInf(mCCIMS->INFO_FILE_NAME);
                mCCIMS->mReadThreadCount -=1;
                qDebug() << "Read info thread finished.";
                break;
            case -2:
                qDebug() << "Read shop thread start.";
                mCCIMS->mReadThreadCount += 1;
                mCCIMS->ReadShop(mCCIMS->SHOP_FILE_NAME);
                mCCIMS->mReadThreadCount -=1;
                qDebug() << "Read shop thread finished.";
                break;
            case -3:
                qDebug() << "Read user thread start.";
                mCCIMS->mReadThreadCount += 1;
                mCCIMS->ReadUser(mCCIMS->USER_FILE_NAME);
                mCCIMS->mReadThreadCount -=1;
                qDebug() << "Read user thread finished.";
                break;
            case 1:
                qDebug() << "Write info thread start.";
                mCCIMS->mWriteThreadCount += 1;
                mCCIMS->WriteInf(mCCIMS->INFO_FILE_NAME);
                mCCIMS->mWriteThreadCount -= 1;
                qDebug() << "Write info thread finished.";
                break;
            case 2:
                //shop无需写入
                break;
            case 3:
                qDebug() << "Write user thread start.";
                mCCIMS->mWriteThreadCount += 1;
                mCCIMS->WriteUser(mCCIMS->USER_FILE_NAME);
                mCCIMS->mWriteThreadCount -= 1;
                qDebug() << "Write user thread finished.";
                break;
            default:
                break;
            }
        }
        JsonThread(CCIMS* c, int t): type(t), mCCIMS(c){}

    private:
        int type;
        CCIMS* mCCIMS;
    };

    QString FilenameCorrect(string filename);       //应对不同平台输出文件路径
    string ReadAllFileToQString(string filename);   //读取文件至std::string

    //写入文件的话，默认一个参数是私有成员变量链表 写进文件
    //注意！默认参数不允许是类内成员变量，原因是编译期无法确定内容，只有静态变量可以当默认参数
    bool ReadInf(string filename);                                  //读入整个信息表文件
    unsigned int ImportInf(string filename);                        //导入整个信息表文件
    bool WriteInf(string filename, Information *info_list = NULL);  //写出指定信息表文件
    bool ReadUser(string filename);                                 //下同
    bool WriteUser(string filename, User *user_list = NULL);
    bool ReadShop(string filename);
    bool WriteShop(string filename, Shop *shop_list =NULL);

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
    Shop*   GetAllShopByNum(int num);       //包括总账户
    QString GetAllNameByNum(int num);       //通过卡号得到用户名？
        int GetUserNum();                   //获取当前用户流水号
    QString GetCurrentUserName();           //获取当前用户名
    User*   GetCurrentUser();
    Shop*   GetCurrentShop();

    //新建消费交易记录，先减少onum的余额，增加inum的余额（可选），
    //并生成流水号、info，插入到表，更新user.json、info.json，
    //返回是否交易成功，money要乘以100
    int NewTransaction(int onum, int inum, int mon);
    int NewAdmTransaction(int year, int month, int day, int hour, int min, int sec, int onum, int inum, int mon);
    bool NewRefund(Information* tempinf);   //撤销某条交易信息
    int NewSubsidy(User* u);                //新建补贴交易
    bool NewRecharge(int num, int money);   //新建充值记录

    //根据当前时间生成流水号，money要乘以100
    string GenerateTag(int onum, int inum, int mon);
    //手动生成流水号，money要乘以100
    string GenerateTag(int year, int month, int day, int hour,
                       int min, int sec, int onum, int inum, int mon);

    //money要乘以100
    Information* BuildInfo(int onum, int inum, int mon);
    Information* BuildInfo(int year, int month, int day, int hour,
                           int min, int sec, int onum, int inum, int mon);

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

    void CouponFresh(); //月初刷新劵额

    int GetProfitByShopNum(int num);
};

#endif // CCIMS_H
