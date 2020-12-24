#ifndef STACK
#define STACK
#include <iostream>

class Stack {
public:
    class Underflow { };
    class Overflow { };
    class Mismatch { };

    virtual void push(int in) = 0;
    virtual int pop(void) = 0;
};
#endif
