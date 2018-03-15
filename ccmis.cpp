#include "ccmis.h"

const string CCMIS::USER_FILE_NAME  = "./user.json";
const string CCMIS::JSON_KEY_NUMBER  = "number";
const string CCMIS::JSON_KEY_NAME  = "name";
const string CCMIS::JSON_KEY_PASSWORD  = "password";

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

        /*User* u = mUser;    //验证数据
        while (u != NULL) {
            cout<<u->number<<"\t"<<u->name<<"\t"<<u->password<<endl;
            u=u->next;
        }*/

        return true;
    } else {
        return false;
    }
}
