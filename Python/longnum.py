import sys
import os

def s_to_i(a):
    return(int(a) - int('0'))

def i_to_s(a):
    return(str(int('0') + int(a)))

def get_index(s, i):
    return (len(s) - i - 1)

def long_num(a, b):
    sumn = ""
    if (len(a) > len(b)):
        ln = a;
        sn = b;
    else:
        ln = b;
        sn = a;

    c = 0
    for i in range(len(sn)):
        # generate index
        li = get_index(ln, i)
        si = get_index(sn, i)

        # add
        s = s_to_i(sn[si]) + s_to_i(ln[li]) + c
        c = int(s/10)
        sumn = i_to_s(s%10) + sumn

    for i in range(len(ln) - len(sn)):
        li = len(ln) - len(sn) - 1 - i
        s = s_to_i(ln[li]) + c
        c = int(s/10)
        sumn = i_to_s(s%10) + sumn

    if c > 0:
        sumn = '1' + sumn

    return sumn


if __name__ == "__main__":
    a = "11199"
    b = "2"

    print(a + " + \n" + b)
    print(long_num(a, b))
