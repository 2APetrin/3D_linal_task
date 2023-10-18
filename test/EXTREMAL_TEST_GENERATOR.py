import random
import numpy as np

inp_range = 100000
range_div = 10

size = 10000
size_div = 1000

num = int( input() )
for i in range(num):
    a = np.array([round(random.randint(-100000, 100000) / range_div, 1), round(random.randint(-1*inp_range, inp_range) / range_div, 1), round(random.randint(-1*inp_range, inp_range) / range_div, 1)])
    for m in range(3):
        for j in range(3):
            print(round(round(random.randint(-1*size, size) / size_div, 1) + round(a[j], 1), 1), end=" ")
