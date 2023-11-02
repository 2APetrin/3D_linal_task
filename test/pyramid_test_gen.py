import random
import numpy as np

num = int(input())

print(num*4)

for i in range(num):
    init_pnt = []
    for j in range(3): # x,y,z coords
        init_pnt.append(random.randint(-100000, 100000))

    coords = []
    for j in range(4):
        for k in range(3):
            coords.append(init_pnt[k] + (random.randint(-100000, 100000) / 10000))

    print(coords[0],coords[1], coords[2], end=" ")
    print(coords[3],coords[4], coords[5], end=" ")
    print(coords[6],coords[7], coords[8], end="\n")

    print(coords[0],coords[1], coords[2], end=" ")
    print(coords[3],coords[4], coords[5],  end=" ")
    print(coords[9],coords[10], coords[11], end="\n")

    print(coords[0],coords[1], coords[2], end=" ")
    print(coords[6],coords[7], coords[8],  end=" ")
    print(coords[9],coords[10], coords[11], end="\n")

    print(coords[3],coords[4], coords[5], end=" ")
    print(coords[6],coords[7], coords[8],  end=" ")
    print(coords[9],coords[10], coords[11], end="\n")


