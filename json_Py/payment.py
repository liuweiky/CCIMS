import json
from pprint import pprint
import numpy as np
import random
import pandas as pd
from datetime import datetime



# shop_arr 普通商店
# bath_arr 洗浴间
with open('shop.json', 'r', encoding="utf8") as f:
    shop = json.load(f)

shop_arr = np.zeros((len(shop)))

for i in range(len(shop)):
    if shop[i]['number'] < 9000:
        shop_arr[i] = shop[i]['number']

shop_arr = [int(x) for x in shop_arr if (x > 0) ]
shop_arr = [int(x) for x in shop_arr if (x %100 != 0) ]

bath_arr = [int(x) for x in shop_arr if (x>3000)and (x<4000)]
din_arr = [int(x) for x in shop_arr if (x>1000) and (x<2000)]
shop_arr = [int(x) for x in shop_arr if (x>2000) and (x<3000)]

# print(shop_arr)
# print(bath_arr)
# print(len(bath_arr))
# print(len(shop_arr))


with open('user_short.json', 'r', encoding="utf8") as u:
    user = json.load(u)

user_arr = np.zeros((len(user)))

for i in range(len(user)):
    if user[i]['number'] < 9000:
        user_arr[i] = user[i]['number']

#stu_arr = [int(x) for x in user_arr if ((x > 4000) and (x < 5000))]
stu_arr = [4001,4002,4003]
tea_arr = [int(x) for x in user_arr if ((x > 5000) and (x < 6000))]
emp_arr = [int(x) for x in user_arr if ((x > 6000) and (x < 7000))]

# print(stu_arr)
# print(tea_arr)
# print(emp_arr)

#读取json完成

#生成随机数函数
def RandomMinAndSec():
    return random.randint(0, 60)

def RandomHour():
    return random.randint(1,24)

def RandomMoneyDinning():
    return random.randint(100,5000)

def RamdomMoneyShop():
    return random.randint(100,10000)

def RandomMoneyBath():
    return random.randint(100,20000)

#生成一条消费记录
def MakeOnePayment(DateTime,Onumber,Inumber,Money):
    tmp_hour = RandomHour()
    tmp_min  = RandomMinAndSec()
    tmp_sec  = RandomMinAndSec()
    tmp_tag  = DateTime[0:4] +DateTime[5:7]+ DateTime[8:10]+str(tmp_hour*10000+tmp_min*100+tmp_sec) \
                + str(Onumber) + str(Inumber) + str(Money)
    return {'year' : int(DateTime[0:4]),
            'month': int(DateTime[5:7]),
            'day': int(DateTime[8:10]),
            'hour':int(tmp_hour),
            'minute':int(tmp_min),
            'sec':int(tmp_sec),
            'onumber':int(Onumber),
            'inumber':int(Inumber),
            'money':int(Money),
            'tag':tmp_tag}


def datelist(beginDate, endDate):
    # beginDate, endDate是datetime格式
    date_l=[datetime.strftime(x,'%Y-%m-%d') \
            for x in list(pd.date_range(start=beginDate, end=endDate))]
    return date_l





whole_date_arr = datelist('2017-01-01','2017-12-31')

def one_stu_whole_payments(stu_index):
    one_stu_din_shop_money = [0 for x in range(len(whole_date_arr))]
    one_stu_payment =[]

    for i in range(len(whole_date_arr)):
        Temp_Dinning_Money =  RandomMoneyDinning()
        while True:
            if (Temp_Dinning_Money + one_stu_din_shop_money[i] < 10000):
                tmp_payment = MakeOnePayment(whole_date_arr[i],stu_arr[stu_index],
                                int(random.choice(din_arr)),Temp_Dinning_Money)
                one_stu_din_shop_money[i] +=Temp_Dinning_Money
                one_stu_payment.append(tmp_payment)
            
                Temp_Shopping_Money = RamdomMoneyShop()
                if(Temp_Shopping_Money + one_stu_din_shop_money[i] < 10000):
                    tmp_payment = MakeOnePayment(whole_date_arr[i],stu_arr[stu_index],
                                int(random.choice(shop_arr)),Temp_Shopping_Money)
                    one_stu_din_shop_money[i] +=Temp_Shopping_Money
                    one_stu_payment.append(tmp_payment)
                else:
                    break
            else:
                break
        if(random.randint(0,1)):
            Temp_Bath_Money = RandomMoneyBath()
            tmp_payment = MakeOnePayment(whole_date_arr[i],stu_arr[stu_index],
                                int(random.choice(bath_arr)),Temp_Bath_Money)
            one_stu_payment.append(tmp_payment)
    return one_stu_payment

all_stu_payment = []
for i in range(len(stu_arr)):
    one_stu = one_stu_whole_payments(i)
    all_stu_payment.extend(one_stu)


with open('ALL_STU_PAYMENTS.json', 'a') as outfile:
    json.dump(all_stu_payment, outfile, ensure_ascii=False,indent=2)