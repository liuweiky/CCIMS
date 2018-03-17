import json
from pprint import pprint
import numpy as np

with open('shop.json', 'r', encoding="utf8") as f:
    shop = json.load(f)

user_arr = np.zeros((len(shop)))

for i in range(len(shop)):
    if shop[i]['number'] < 9000:
        user_arr[i] = shop[i]['number']

user_arr = [int(x) for x in user_arr if x > 0]

print(user_arr)

with open('user_short.json', 'r', encoding="utf8") as u:
    user = json.load(u)

user_arr = np.zeros((len(user)))

for i in range(len(user)):
    if user[i]['number'] < 9000:
        user_arr[i] = user[i]['number']

stu_arr = [int(x) for x in user_arr if ((x > 4000) and (x < 5000))]
tea_arr = [int(x) for x in user_arr if ((x > 5000) and (x < 6000))]
emp_arr = [int(x) for x in user_arr if ((x > 6000) and (x < 7000))]

print(stu_arr)
print(tea_arr)
print(emp_arr)
