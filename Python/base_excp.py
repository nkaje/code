#!/usr/bin/python3

def do_stuff(a, i):
    try:
        raise SystemExit("a is false")
    except BaseException as e:
        if i == True:
            pass


do_stuff(True, False)

do_stuff(False, False)

