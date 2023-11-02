import random
import numpy as np

print (100000)
for i in range(10000):
    x=random.randint(-100000, 100000)
    y=random.randint(-100000, 100000)
    for j in range(3):
        print(x + random.randint(-100000, 100000)/1000, y + random.randint(-100000, 100000)/1000, 0.0001, end=" ")

    print()
