#include "ccmis.h"
#include <QFile>
#include "common_funcs.h"
#include <QTextStream>
#include <QDebug>
const string CCMIS::USER_FILE_NAME  = "user.json";
const string CCMIS::SHOP_FILE_NAME  = "shop.json";
const string CCMIS::INFO_FILE_NAME  = "info.json";

const string CCMIS::JSON_KEY_NUMBER  = "number";
const string CCMIS::JSON_KEY_NAME  = "name";
const string CCMIS::JSON_KEY_PASSWORD  = "password";
const string CCMIS::JSON_KEY_BALANCE  = "balance";
const string CCMIS::JSON_KEY_COUPON  = "coupon";

const string CCMIS::JSON_KEY_TAG = "tag";
const string CCMIS::JSON_KEY_YEAR = "year";
const string CCMIS::JSON_KEY_MONTH = "month";
const string CCMIS::JSON_KEY_DAY = "day";
const string CCMIS::JSON_KEY_HOUR = "hour";
const string CCMIS::JSON_KEY_MINUTE = "minute";
const string CCMIS::JSON_KEY_SECOND = "second";
const string CCMIS::JSON_KEY_ONUMBER = "onumber";
const string CCMIS::JSON_KEY_INUMBER = "inumber";
const string CCMIS::JSON_KEY_MONEY = "money";

const int CCMIS::SUPERUSER_BEGIN = 0;
const int CCMIS::SUPERUSER_END = 999;
const int CCMIS::SHOP_CANTEEN_BEGIN = 1101;
const int CCMIS::SHOP_CANTEEN_END = 1999;
const int CCMIS::SHOP_MARKET_BEGIN = 2101;
const int CCMIS::SHOP_MARKET_END = 2999;
const int CCMIS::SHOP_BATH_BEGIN = 3101;
const int CCMIS::SHOP_BATH_END = 3999;
const int CCMIS::SHOP_BEGIN = 1000;
const int CCMIS::SHOP_END = 3999;
const int CCMIS::USER_TEA_EMP_BEGIN = 5000;
const int CCMIS::USER_TEA_EMP_END = 6999;
const int CCMIS::USER_BEGIN = 4000;
const int CCMIS::USER_END = 6999;

const int CCMIS::MESSAGE_TRANSACTION_SUCCESS = 0;
const int CCMIS::MESSAGE_TRANSACTION_NO_USER = -1;
const int CCMIS::MESSAGE_TRANSACTION_NO_SHOP = -2;
const int CCMIS::MESSAGE_TRANSACTION_OVERFLOW = -3;
const int CCMIS::MESSAGE_TRANSACTION_BALANCE_NOT_ENOUGH = -4;
const int CCMIS::MESSAGE_TRANSACTION_MONEY_LOWER_THAN_ZERO = -5;
const int CCMIS::MESSAGE_TRANSACTION_UNKNOWN = -6;

const int CCMIS::GROUP_SUPERUSER = 0;
const int CCMIS::GROUP_CANTEEN = 1;
const int CCMIS::GROUP_MARKET = 2;
const int CCMIS::GROUP_BATH = 3;

CCMIS::CCMIS()
{
    mUserNumber = -1;

    mInfo = new Information();
    mShop = new Shop();
    mUser = new User();

    mInfo->next = NULL;
    mShop->next = NULL;
    mUser->next = NULL;

    totalInfoCount = 0;
    totalShopCount = 0;
    totalUserCount = 0;

    if (!ReadUser(USER_FILE_NAME))  //判断打开文件是否成功
    {
        cout << "Open " + USER_FILE_NAME + " failed.";
    }

    if (!ReadShop(SHOP_FILE_NAME))
    {
        cout << "Open " + SHOP_FILE_NAME + " failed.";
    }

    //WriteUser(USER_FILE_NAME);

    //GenerateTag(6998, 1101, 1500);

    //InsertInf(BuildInfo(6998, 1101, 1500));
    //WriteInf(INFO_FILE_NAME);

    if (!ReadInf(INFO_FILE_NAME))
    {
        cout << "Open " + INFO_FILE_NAME + " failed.";
    }

    cout<<GetTotalCanteenConsumptionByDay(2018,1,3,4001)<<endl;
    cout<<GetUserByNum(4000)<<endl;

//    cout << "start transaction...\n";
//    time_t timep;
//    time (&timep);
//    char timestr[64];
//    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S",localtime(&timep));
//    cout<<"start: "<<timestr<<endl;
//    cout << NewTransaction(4001, 3101, 2500)<<endl;


//    time (&timep);
//    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S",localtime(&timep));
//    cout<<"end: "<<timestr<<endl;

//    cout << "transaction complete...\n";
}

bool CCMIS::WriteUser(string filename)
{
    QFile fileOut(COMMON_FUNCS::UTF8ToQString(filename));
    if(!fileOut.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug("Could not open the file for WRITING! \n");
        return false;
    }


    jsonxx::Array array;

//    ofstream out(USER_FILE_NAME);

//    if (!out.is_open())
//        return false;

    User* u = mUser->next;
    while (u != NULL) {
        jsonxx::Object obj;
        obj << JSON_KEY_NUMBER << u->number;
        obj << JSON_KEY_NAME << COMMON_FUNCS::ToUTF8String(u->name);
        obj << JSON_KEY_PASSWORD << u->password;
        obj << JSON_KEY_BALANCE << u->balance;
        obj << JSON_KEY_COUPON << u->coupon;
        array << obj;
        u=u->next;
    }
    QString allJsonArray = COMMON_FUNCS::UTF8ToQString(array.json());
    QTextStream streamFileOut(&fileOut);
    streamFileOut.setCodec("UTF-8");
    streamFileOut<<allJsonArray;
    streamFileOut.flush();
    fileOut.close();

    /*
    out << array.json();
    out.close();*/
    return true;
}

string CCMIS::ReadAllFileToQString(string filename){

    QFile fileReadIn(COMMON_FUNCS::UTF8ToQString(filename));
    if(!fileReadIn.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("Could not open the file for reading \n");
        return string("");
        //String("").Empty();  //结果为true判定用
    }
    QString allLine;
    QTextStream readInSteam(&fileReadIn);
    readInSteam.setCodec("UTF-8");
    while (!readInSteam.atEnd()) {
        QString line = readInSteam.readLine();
        line += '\n';
        allLine +=line;
    }

    fileReadIn.close();
    string  cstr = allLine.toStdString();
    return cstr;


}






bool CCMIS::ReadUser(string filename)
{
    /**by liuvv*/
    //change by wangzl using qfile, coding with utf-8

   // ifstream in(filename);

    string fileALLReadIn = ReadAllFileToQString(filename);
    if (!fileALLReadIn.empty())
    {/*
        ostringstream tmp;
        tmp << in.rdbuf();
        string s;
        s = tmp.str();
        in.close();

        //cout<<s;*/


        jsonxx::Array array;

       // array.parse(s);
        //解析 json

        array.parse(fileALLReadIn);



        for (size_t i = 0; i < array.size(); i++)  //迭代构造
        {
            User* u = new User();

            u->number = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_NUMBER);
            u->name = COMMON_FUNCS::UTF8ToQString(array.get<jsonxx::Object>(i).get<jsonxx::String>(JSON_KEY_NAME));
            u->password = array.get<jsonxx::Object>(i).get<jsonxx::String>(JSON_KEY_PASSWORD);
            u->balance = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_BALANCE);
            u->coupon = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_COUPON);

            /**DON NOT DELETE THE ANNOTATION RASHLY!!!*/
            /*u->balance = (rand() % (100000 - 0 + 1)) + 0;
            if (u->number < 5000)
            {
                u->coupon = (rand() % (10000 - 0 + 1)) + 0;
            } else {
                u->coupon = 0;
            }*/

            u->next = mUser->next;
            mUser->next = u;
            //统计用户数
            totalUserCount++;

        }

        User* u = mUser->next;    //验证数据
        while (u != NULL) {
            cout<<u->number<<"\t"<<u->name<<"\t"<<u->password<<"\t"<<u->balance<<"\t"<<u->coupon<<endl;
            u=u->next;
        }

        return true;
    } else {
        return false;
    }
}

bool CCMIS::ReadShop(string filename)
{
    /**by liuvv*/
    //change by wangzl using qfile, coding with utf-8

   // ifstream in(filename);

    string fileALLReadIn = ReadAllFileToQString(filename);
    if (!fileALLReadIn.empty())
    {
//        ostringstream tmp;
//        tmp << in.rdbuf();
//        string s;
//        s = tmp.str();
//        in.close();

//        //cout<<s;

       jsonxx::Array array;

        //array.parse(s); //解析 json

        array.parse(fileALLReadIn);

        //cout<<array.json();

        for (int i = 0; i < array.size(); i++)  //迭代构造
        {
            Shop* s = new Shop();

            s->number = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_NUMBER);
            s->name = COMMON_FUNCS::UTF8ToQString(array.get<jsonxx::Object>(i).get<jsonxx::String>(JSON_KEY_NAME));
            s->password = array.get<jsonxx::Object>(i).get<jsonxx::String>(JSON_KEY_PASSWORD);

            s->next = mShop->next;
            mShop->next = s;

            //统计商铺数
            totalShopCount++;
        }

        Shop* sh = mShop->next;    //验证数据
        while (sh != NULL) {
            cout<<sh->number<<"\t"<<sh->name<<"\t"<<sh->password<<endl;
            sh=sh->next;
        }

        return true;
    } else {
        return false;
    }
}

string CCMIS::GenerateTag(int onum, int inum, int mon)
{
    time_t tt = time(NULL);
    tm* t= localtime(&tt);

    /**TIME*/
    string tag = to_string(t->tm_year + 1900);

    tag += t->tm_mon + 1 < 10 ? "0" + to_string(t->tm_mon + 1) : to_string(t->tm_mon + 1);
    tag += t->tm_mday < 10 ? "0" + to_string(t->tm_mday) : to_string(t->tm_mday);
    tag += t->tm_hour < 10 ? "0" + to_string(t->tm_hour) : to_string(t->tm_hour);
    tag += t->tm_min < 10 ? "0" + to_string(t->tm_min) : to_string(t->tm_min);
    tag += t->tm_sec < 10 ? "0" + to_string(t->tm_sec) : to_string(t->tm_sec);

    /**I/O NUMBER*/
    tag += onum < 1000 ? "000" + to_string(onum) : to_string(onum);
    tag += inum < 1000 ? "000" + to_string(inum) : to_string(inum);

    /**COST*/
    if (mon < 10)
    {
        tag += "0000" + to_string(mon);
    } else if (mon < 100)
    {
        tag += "000" + to_string(mon);
    } else if (mon < 1000)
    {
        tag += "00" + to_string(mon);
    } else if (mon < 10000)
    {
        tag += "0" + to_string(mon);
    } else {
        tag += to_string(mon);
    }


    cout<<tag<<endl;

    return tag;
}





void CCMIS::InsertInf(Information* tempinf)
{
    tempinf->next = mInfo->next;
    mInfo->next = tempinf;
    totalInfoCount++;
}

Information* CCMIS::BuildInfo(int onum, int inum, int mon)
{
    Information* info = new Information();
    info->tag = GenerateTag(onum, inum, mon);

    time_t tt = time(NULL);
    tm* t= localtime(&tt);

    info->year = t->tm_year + 1900;
    info->month = t->tm_mon + 1;
    info->day = t->tm_mday;
    info->hour = t->tm_hour;
    info->minute = t->tm_min;
    info->second = t->tm_sec;

    info->Onumber = onum;
    info->Inumber = inum;
    info->money = mon;

    info->next = NULL;
}

bool CCMIS::WriteInf(string filename)
{
    jsonxx::Array array;

    QFile fileOut(COMMON_FUNCS::UTF8ToQString(filename));
    if(!fileOut.open(QIODevice::WriteOnly|QIODevice::Text)){
       qDebug("Could not open the file for WRITING!\n");
       return false;
    }
//    ofstream out(INFO_FILE_NAME);

//    if (!out.is_open())
//        return false;

    Information* i = mInfo->next;
    while (i != NULL) {
        jsonxx::Object obj;

        obj << JSON_KEY_TAG << i->tag;
        obj << JSON_KEY_YEAR << i->year;
        obj << JSON_KEY_MONTH << i->month;
        obj << JSON_KEY_DAY << i->day;
        obj << JSON_KEY_HOUR << i->hour;
        obj << JSON_KEY_MINUTE << i->minute;
        obj << JSON_KEY_SECOND << i->second;
        obj << JSON_KEY_ONUMBER << i->Onumber;
        obj << JSON_KEY_INUMBER << i->Inumber;
        obj << JSON_KEY_MONEY << i->money;

        array << obj;

        i=i->next;
    }

    QString allJsonArray = COMMON_FUNCS::UTF8ToQString(array.json());
    QTextStream streamFileOut(&fileOut);
    streamFileOut.setCodec("UTF-8");
    streamFileOut<<allJsonArray;
    streamFileOut.flush();
    fileOut.close();
//    out << array.json();
//    out.close();
    return true;
}


bool CCMIS::ReadInf(string filename)
{
//    ifstream in(filename);
    string fileALLReadIn = ReadAllFileToQString(filename);
    if (!fileALLReadIn.empty())
    {
//        ostringstream tmp;
//        tmp << in.rdbuf();
//        string s;
//        s = tmp.str();
//        in.close();

        //cout<<s;

        jsonxx::Array array;

        array.parse(fileALLReadIn); //解析 json

        //cout<<array.json();

        for (int i = 0; i < array.size(); i++)  //迭代构造
        {
            Information* info = new Information();

            info->tag = array.get<jsonxx::Object>(i).get<jsonxx::String>(JSON_KEY_TAG);
            info->year = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_YEAR);
            info->month = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_MONTH);
            info->day = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_DAY);
            info->hour = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_HOUR);
            info->minute = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_MINUTE);
            info->second = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_SECOND);
            info->Inumber= array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_INUMBER);
            info->Onumber= array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_ONUMBER);
            info->money= array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_MONEY);

            info->next = mInfo->next;
            mInfo->next = info;
            //统计记录数目
            totalInfoCount++;
        }

        /*Information* info = mInfo->next;    //验证数据
        while (info != NULL) {
            cout
                 <<info->tag<<"\t"
                 <<info->year<<"\t"
                 <<info->month<<"\t"
                 <<info->day<<"\t"
                 <<info->hour<<"\t"
                 <<info->minute<<"\t"
                 <<info->second<<"\t"
                 <<info->Inumber<<"\t"
                 <<info->Onumber<<"\t"
                 <<info->money<<endl;
            info=info->next;
        }*/

        return true;
    } else {
        return false;
    }
}

bool CCMIS::CheckPassword(string password)
{
    if (mUserNumber == -1) return false;    //用户名未初始化

    if (mUserNumber < 4000) //店家登录
    {
        Shop* s = mShop->next;
        while (s != NULL) {
            if (s->number == mUserNumber)
                break;
            s = s->next;
        }

        if (s !=NULL && password.compare(s->password) == 0)
            return true;
        else return false;
    } else {    //教职工登录
        User* u = mUser->next;
        while (u != NULL) {
            if (u->number == mUserNumber)
                break;
            u = u->next;
        }

        if (u !=NULL && password.compare(u->password) == 0)
            return true;
        else return false;
    }


}

void CCMIS::SetUserNumber(int n)
{
    mUserNumber = n;
}

Information* CCMIS::GetInfoPointer()
{
    return mInfo;
}

unsigned int CCMIS::GetTotalInfoNumber()
{
    return totalInfoCount;
}


unsigned int CCMIS::GetTotalUserNumber()
{
    return totalUserCount;
}


unsigned int CCMIS::GetTotalShopNumber()
{
    return totalShopCount;
}



//默认统计补贴信息 onum=2
Information* CCMIS::SearchInfoByOnum(int onum , unsigned long start_date_num,unsigned int start_time_num ,
                                     unsigned long finish_date_num ,unsigned int finish_time_num )
{
    Information* filter_info_list = new Information();
    filter_info_list->next = NULL;

    Information* info = mInfo->next;

    unsigned long long start   = start_date_num *  1000000 + start_time_num;
    unsigned long long finish  = finish_date_num * 1000000 + finish_time_num;
    while(info!=NULL){

        if( info->Onumber == onum ){
            unsigned long  info_date = Date::DateToNum(info->year,info->month,info->day);
            unsigned int info_time = Time::TimeToNum(info->hour,info->minute);
            unsigned long long  info_cur = info_date * 1000000 + info_time;
            if( info_cur>=start && info_cur <=finish ){
                    Information* filtered_one_info = new Information();
                    Information::CopyOneInfo(info,filtered_one_info);
                    filtered_one_info->next = filter_info_list->next;
                    filter_info_list -> next = filtered_one_info;
            }
        }
        info = info->next;

    }
    return filter_info_list;
}

Information* CCMIS::SearchInfoByInum(int inum, unsigned long start_date_num,unsigned int start_time_num,
                                     unsigned long finish_date_num,unsigned int finish_time_num)
{
    Information* filter_info_list = new Information();
    filter_info_list->next = NULL;

    Information* info = mInfo->next;

    unsigned long long start   = start_date_num *  1000000 + start_time_num;
    unsigned long long finish  = finish_date_num * 1000000 + finish_time_num;
    while(info!=NULL){

        if( info->Inumber == inum ){
            unsigned long  info_date = Date::DateToNum(info->year,info->month,info->day);
            unsigned int info_time = Time::TimeToNum(info->hour,info->minute);
            unsigned long long  info_cur = info_date * 1000000 + info_time;
            if( info_cur>=start && info_cur <=finish ){
                    Information* filtered_one_info = new Information();
                    Information::CopyOneInfo(info,filtered_one_info);
                    filtered_one_info->next = filter_info_list->next;
                    filter_info_list -> next = filtered_one_info;
            }
        }
        info = info->next;

    }
    return filter_info_list;

}






void CCMIS::DeleteInf(Information *tempinf)
{
    if (tempinf == NULL)
        return;

    Information* i = mInfo->next;
    while (i != NULL) {
        if (i->next == tempinf)
            break;
        i = i->next;
    }

    if (i != NULL)
    {
        i->next = tempinf->next;
    }

    delete tempinf;

    totalInfoCount--;
}

User* CCMIS::GetUserByNum(int num)
{
    if (num >= USER_BEGIN && num <= USER_END)
    {
        User* u = mUser->next;
        while (u !=NULL) {
            if (u->number == num)
                return u;
            u = u->next;
        }

        return NULL;
    } else {
        return NULL;
    }
}



Shop* CCMIS::GetShopByNum(int num)
{
    if (
            (num >= SHOP_CANTEEN_BEGIN &&
            num <= SHOP_CANTEEN_END) ||
            (num >= SHOP_MARKET_BEGIN &&
             num <= SHOP_MARKET_END) ||
            (num >= SHOP_BATH_BEGIN &&
            num <= SHOP_BATH_END))   //防止越权取得0、1、2号用户权限
    {
        Shop* s = mShop->next;
        while (s != NULL) {
            if (s->number == num)
                return s;
            s = s->next;
        }

        return NULL;
    } else {
        return NULL;
    }


}


QString CCMIS::GetAllNameByNum(int num)
{
    switch (num) {
    case 0:
        return QString::fromUtf8("总入账账户");
        break;
    case 1:
        return QString::fromUtf8("充值账户");
    case 2:
        return QString::fromUtf8("返补助账户");
    default:
    {
        User* temp_user = GetUserByNum(num);
        Shop* temp_shop = GetShopByNum(num);
        if(temp_shop)
            return temp_shop->name;
        else if(temp_user)
            return temp_user->name;
        else
            return QString::fromUtf8("用户不存在");
        break;
    }
    }

}



int CCMIS::GetTotalCanteenConsumptionByDay(int year, int month, int day, int num)
{
    int c =0;
    Information* info = mInfo->next;
    while (info != NULL) {
        if (
                info->Inumber / 1000 == GROUP_CANTEEN &&
                info->year == year &&
                info->month == month &&
                info->day == day &&
                info->Onumber == num)
        {
            c += info->money;
        }

        info = info->next;
    }

    return c;
}

int CCMIS::GetTotalCanteenAndMarketConsumptionByDay(int year, int month, int day, int num)
{
    int c =0;
    Information* info = mInfo->next;
    while (info != NULL) {
        if (
                (info->Inumber / 1000 == GROUP_CANTEEN ||
                 info->Inumber / 1000 == GROUP_MARKET) &&
                info->year == year &&
                info->month == month &&
                info->day == day &&
                info->Onumber == num)
        {
            c += info->money;
        }

        info = info->next;
    }

    return c;
}

int CCMIS::NewSubsidy(User* u)
{
    if (u->number >= USER_TEA_EMP_BEGIN && u->number <= USER_TEA_EMP_END)   //教职工单次消费超20
    {
        u->balance += 500;
        WriteUser(USER_FILE_NAME);

        Information* info = BuildInfo(2, u->number, 500);
        InsertInf(info);
        WriteInf(INFO_FILE_NAME);
    }

}

int CCMIS::NewTransaction(int onum, int inum, int mon)
{
    if (mon <= 0)
        return MESSAGE_TRANSACTION_MONEY_LOWER_THAN_ZERO;

    User* u = GetUserByNum(onum);
    if (u == NULL)
        return MESSAGE_TRANSACTION_NO_USER;   //学生、教职工号不存在，交易失败

    Shop* s = GetShopByNum(inum);
    if (s == NULL)
        return MESSAGE_TRANSACTION_NO_SHOP;   //商号不存在，交易失败

    time_t tt = time(NULL);
    tm* t= localtime(&tt);

    if (inum / 1000 == GROUP_CANTEEN)   //收款方是食堂组
    {
        if (
                mon > 5000 ||
                GetTotalCanteenConsumptionByDay(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, onum) + mon > 10000)
        {
            return MESSAGE_TRANSACTION_OVERFLOW;    //超过每笔消费或单日限制
        } else {    //交易条件具备，开始交易

            if (u->balance < mon)  //余额不足
                return MESSAGE_TRANSACTION_BALANCE_NOT_ENOUGH;

            u->balance -= mon;
            WriteUser(USER_FILE_NAME);
            Information* info = BuildInfo(onum, inum, mon);
            InsertInf(info);
            WriteInf(INFO_FILE_NAME);

            if (u->number >= USER_TEA_EMP_BEGIN && u->number <= USER_TEA_EMP_END && mon > 2000)   //教职工单次消费超20
            {
                NewSubsidy(u);
            }

            return MESSAGE_TRANSACTION_SUCCESS;
        }
    } else if (inum / 1000 == GROUP_MARKET) {   //收款方是超市组
        if (
                GetTotalCanteenAndMarketConsumptionByDay(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, onum) + mon > 10000)
        {
            return MESSAGE_TRANSACTION_OVERFLOW;    //超过单日限制
        } else {
            if (u->balance < mon)  //余额不足
                return MESSAGE_TRANSACTION_BALANCE_NOT_ENOUGH;

            u->balance -= mon;
            WriteUser(USER_FILE_NAME);
            Information* info = BuildInfo(onum, inum, mon);
            InsertInf(info);
            WriteInf(INFO_FILE_NAME);

            return MESSAGE_TRANSACTION_SUCCESS;
        }
    } else if (inum / 1000 == GROUP_BATH) {
        if (u->balance + u->coupon < mon)   //余额不足
            return MESSAGE_TRANSACTION_BALANCE_NOT_ENOUGH;

        if (mon < 200)
            mon = 200;    //至少消费2元

        if (u->coupon > 0)   //洗漱券有余额
        {
            if (u->coupon >= mon)   //洗漱券余额超过 mon
            {
                u->coupon -= mon;
            } else {    //否则先扣coupon，再扣balance
                u->balance -= (mon - u->coupon);

                u->coupon = 0;
            }
        } else {
            u->balance -= mon;
        }

        WriteUser(USER_FILE_NAME);
        Information* info = BuildInfo(onum, inum, mon);
        InsertInf(info);
        WriteInf(INFO_FILE_NAME);

        return MESSAGE_TRANSACTION_SUCCESS;
    }

    return MESSAGE_TRANSACTION_UNKNOWN; //未知错误
}

bool CCMIS::NewRefund(Information *tempinf)
{
    User* u = mUser->next;
    while (u != NULL) {
        if (u->number == tempinf->Onumber)
            break;
        u = u->next;
    }

    if (u == NULL)
        return false;

    u->balance += tempinf->money;
    DeleteInf(tempinf);

    WriteUser(USER_FILE_NAME);
    WriteInf(INFO_FILE_NAME);

    return true;
}

int CCMIS::GetUserNum()
{
    return mUserNumber;
}

bool CCMIS::NewRecharge(int num, int money)
{
    User* u = GetUserByNum(num);
    u->balance += money;
    Information* info = BuildInfo(1, num, money);
    InsertInf(info);

    return WriteUser(USER_FILE_NAME) && WriteInf(INFO_FILE_NAME);
}
