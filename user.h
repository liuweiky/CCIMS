#ifndef USER_H
#define USER_H

#include <string>


/*int SYS_TOTAL = 9000;       //总入账账户
int SYS_RECHARGE = 9001;    //"充值账户（出账）"
int SYS_ALLOWANCE = 9002;   //"返补助账户"
int SHOP_START = 1000;      //商户起始（总商户统计）
int SHOP_END = 3999;        //商户截止
int STU_START = 4000;       //下同
int STU_END = 4999;
int TEA_EMP_START = 5000;
int TEA_EMP_END = 6999;*/




struct User
{
    int     number;
    string  name;
    string  password;
    int     balance;    //余额
    int     coupon;     //劵
    User*   next;   //下个结点
};

#endif // USER_H
