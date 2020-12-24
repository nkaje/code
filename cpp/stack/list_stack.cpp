#include "list_stack.h"

int List_stack::pop()
{
    int x = lc.front();
    lc.pop_front();
    return x;
}
