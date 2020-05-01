#!/bin/python3

import sys
import os

# Sample parse.txt
#493187
#493589
#493991
#494393
#494795
#495197
#495599

try:
    fp = open("./parse.txt")
except:
    SystemExit("failed to openfile")

prev = 0
cum = 0
with open("./parse.txt") as fp:
    for line in fp:
        line  = fp.readline()
        cur = int(line)
        if (prev > cur):
            print("%d and %d are not in increasing order", prev, cur)
            raise SystemExit()
        else:
            print("%d < %d: ok" % (prev, cur))
        cum = cum + (cur - prev)
        prev = cur

print("Cumulative chunk size %d" % cum)
