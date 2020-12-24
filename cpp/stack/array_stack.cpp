#include "array_stack.h"
#define MAX_SIZE 200

Array_stack::Array_stack(int s)
{
   max_size = MAX_SIZE;
   top = 0;
   if (s > max_size)
       throw Stack::Mismatch();
   Array_stack::p = new int[s];
}

Array_stack::~Array_stack(void)
{
    delete p;
}

void Array_stack::push(int in)
{
    if (top >= max_size)
        throw Stack::Overflow();

    p[top++] = in;
}

int Array_stack::pop(void)
{
    if (top == 0)
        throw Stack::Underflow();

    return p[--top];
}
