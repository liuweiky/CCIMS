import json
from pprint import pprint
import numpy as np
import random

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
shop_arr = [int(x) for x in shop_arr if (x>1000) and (x<3000)]

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

stu_arr = [int(x) for x in user_arr if ((x > 4000) and (x < 5000))]
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


total_month = [x + 201700 for x in range(1,13)]


for i in range(len(total_month)):
    