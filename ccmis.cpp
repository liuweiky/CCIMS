#include "ccmis.h"

const string CCMIS::USER_FILE_NAME  = "./user.json";
const string CCMIS::SHOP_FILE_NAME  = "./shop.json";
const string CCMIS::MONEY_FILE_NAME  = "./money.json";

const string CCMIS::JSON_KEY_NUMBER  = "number";
const string CCMIS::JSON_KEY_NAME  = "name";
const string CCMIS::JSON_KEY_PASSWORD  = "password";
const string CCMIS::JSON_KEY_BALANCE  = "balance";
const string CCMIS::JSON_KEY_COUPON  = "coupon";

const int CCMIS::GROUP_SUPERUSER = 0;
const int CCMIS::GROUP_CANTEEN = 1;
const int CCMIS::GROUP_MARKET = 2;
const int CCMIS::GROUP_BATH = 3;

bool CCMIS::GenerateRandomMoney()
{
    jsonxx::Array array;

    jsonxx::Object obj0;
    obj0 << JSON_KEY_NUMBER << 0;
    obj0 << JSON_KEY_BALANCE << 0;
    obj0 << JSON_KEY_COUPON << 0;



    array << obj0;

    obj0 << JSON_KEY_NUMBER << 1;
    array << obj0;
    obj0 << JSON_KEY_NUMBER << 2;
    array << obj0;



    for (int i = 4000; i <= 6999; i++)
    {
        jsonxx::Object obj;
        obj << JSON_KEY_NUMBER << i;
        obj << JSON_KEY_BALANCE
            << (rand() % (100000 - 0 + 1)) + 0;
        if (i < 5000)
        {
            obj << JSON_KEY_COUPON
                << (rand() % (10000 - 0 + 1)) + 0;
        } else {
            obj << JSON_KEY_COUPON <<0;
        }
        array << obj;
    }

    cout << array.json();

    ofstream out(MONEY_FILE_NAME);

    if (out.is_open())
    {
        out << array.json();
        out.close();
    } else {
        cout << "Write " + MONEY_FILE_NAME + " failed.";
    }
}

CCMIS::CCMIS()
{
    mInfo = new Information();
    mMoney = new Money();
    mShop = new Shop();
    mUser = new User();

    mInfo->next = NULL;
    mMoney->next = NULL;
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

            u->next = mUser->next;
            mUser->next = u;
        }

        User* u = mUser->next;    //验证数据
        while (u != NULL) {
            cout<<u->number<<"\t"<<u->name<<"\t"<<u->password<<endl;
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

