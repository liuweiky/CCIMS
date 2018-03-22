#ifndef USER_H
#define USER_H

#include <QString>
#include <string>





struct User
{
    int     number;
    QString  name;
    std::string  password;
    int     balance;    //余额
    int     coupon;     //劵
    User*   next;   //下个结点
};

#endif // USER_H
