#ifndef SHOP_H
#define SHOP_H

#include <QString>
#include <string>

struct Shop
{
    int     number;
    QString  name;
    std::string  password;
    Shop*  next;    //下个结点
};

#endif // SHOP_H
