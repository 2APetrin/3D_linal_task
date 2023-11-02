import random
import numpy as np

num = int(input())
print (num * 100)
for i in range(100):
    for k in range(num):
        x=random.randint(-100000, 100000)
        y=random.randint(-100000, 100000)
        for j in range(3):
            print(x + random.randint(-100000, 100000)/1000, y + random.randint(-100000, 100000)/1000, 0.0001*i, end=" ")

        print()
