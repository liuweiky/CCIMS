#ifndef SHOP_H
#define SHOP_H

#include <string>

struct Shop
{
    int     number;
    std::string  name;
    std::string  password;
    Shop*  next;    //下个结点
};

#endif // SHOP_H
