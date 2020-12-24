#include "stack.h"

class Array_stack : public Stack {
    int *p;
    int max_size;
    int top;
public:
    Array_stack(int s);
    ~Array_stack();

    void push(int in);
    int pop(void);
};
