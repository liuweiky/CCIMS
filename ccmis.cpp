#include "ccmis.h"

const string CCMIS::USER_FILE_NAME  = "./user.json";
const string CCMIS::SHOP_FILE_NAME  = "./shop.json";

const string CCMIS::JSON_KEY_NUMBER  = "number";
const string CCMIS::JSON_KEY_NAME  = "name";
const string CCMIS::JSON_KEY_PASSWORD  = "password";
const string CCMIS::JSON_KEY_BALANCE  = "balance";
const string CCMIS::JSON_KEY_COUPON  = "coupon";

const int CCMIS::GROUP_SUPERUSER = 0;
const int CCMIS::GROUP_CANTEEN = 1;
const int CCMIS::GROUP_MARKET = 2;
const int CCMIS::GROUP_BATH = 3;

CCMIS::CCMIS()
{
    mInfo = new Information();
    mShop = new Shop();
    mUser = new User();

    mInfo->next = NULL;
    mShop->next = NULL;
    mUser->next = NULL;


    if (!ReadUser(USER_FILE_NAME))  //判断打开文件是否成功
    {
        cout << "Open " + USER_FILE_NAME + " failed.";
    }

    if (!ReadShop(SHOP_FILE_NAME))
    {
        cout << "Open " + SHOP_FILE_NAME + " failed.";
    }

    //WriteUser(USER_FILE_NAME);

    GenerateTag(6998, 1101, 1500);
}

bool CCMIS::WriteUser(string filename)
{
    jsonxx::Array array;

    ofstream out(USER_FILE_NAME);

    if (!out.is_open())
        return false;

    User* u = mUser->next;
    while (u != NULL) {
        //cout<<u->number<<"\t"<<u->name<<"\t"<<u->password<<endl;

        jsonxx::Object obj;

        obj << JSON_KEY_NUMBER << u->number;
        obj << JSON_KEY_NAME << u->name;
        obj << JSON_KEY_PASSWORD << u->password;
        obj << JSON_KEY_BALANCE << u->balance;
        obj << JSON_KEY_COUPON << u->coupon;

        array << obj;

        u=u->next;
    }

    out << array.json();
    out.close();
    return true;
}
bool CCMIS::ReadUser(string filename)
{
    /**by liuvv*/
    ifstream in(filename);

    if (in.is_open())
    {
        ostringstream tmp;
        tmp << in.rdbuf();
        string s;
        s = tmp.str();
        in.close();

        //cout<<s;

        jsonxx::Array array;

        array.parse(s); //解析 json

        //cout<<array.json();

        for (int i = 0; i < array.size(); i++)  //迭代构造
        {
            User* u = new User();

            u->number = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_NUMBER);
            u->name = array.get<jsonxx::Object>(i).get<jsonxx::String>(JSON_KEY_NAME);
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
    ifstream in(filename);

    if (in.is_open())
    {
        ostringstream tmp;
        tmp << in.rdbuf();
        string s;
        s = tmp.str();
        in.close();

        //cout<<s;

        jsonxx::Array array;

        array.parse(s); //解析 json

        //cout<<array.json();

        for (int i = 0; i < array.size(); i++)  //迭代构造
        {
            Shop* s = new Shop();

            s->number = array.get<jsonxx::Object>(i).get<jsonxx::Number>(JSON_KEY_NUMBER);
            s->name = array.get<jsonxx::Object>(i).get<jsonxx::String>(JSON_KEY_NAME);
            s->password = array.get<jsonxx::Object>(i).get<jsonxx::String>(JSON_KEY_PASSWORD);

            s->next = mShop->next;
            mShop->next = s;
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
    time_t tt = time(NULL);//这句返回的只是一个时间cuo
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


    cout<<tag;

    return tag;
}
