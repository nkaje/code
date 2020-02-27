#/bin/python3

class MyExceptionWithContext(Exception):
    def __init___(self,dErrorArguments):
        print(dErrorArguments)
        Exception.__init__(self,"my exception was raised with arguments {0}".format(dErrArguments))
        self.dErrorArguments = dErrorArguements
        
def do_stuff(a,b,c):
    if ((a != b)) and (c == 1):
        raise MyExceptionWithContext({
                'a' : a,
                'b' : b,
                'c' : c,
                })
    else:
        print("no exception")

do_stuff(1, 1, 1)
do_stuff(1, 2, 1)

