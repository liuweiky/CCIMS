#ifndef MONEY_H
#define MONEY_H

struct Money
{
    int     number;     //卡号
    int     balance;    //余额
    int     coupon;     //劵
    Money*  next;       //下个结点
};

#endif // MONEY_H
