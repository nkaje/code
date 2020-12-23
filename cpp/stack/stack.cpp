#include "stack.h"
#include <iostream>
using namespace std;

namespace Stack {
    const int max_size = 200;
    int v[max_size];
    int top = 0;
};

using namespace Stack;

void Stack::push(int in)
{
    if (top < max_size) {
        v[top++] = in;
    } else {
        cout << "Exceeded size\n";
        throw Overflow();
    }
}

int Stack::pop(void)
{
    int ret = -1;

    if (top > 0) {
        ret = v[--top];
    } else {
        cout << "Empty stack\n";
        throw Overflow();
    }

    return ret;
}
