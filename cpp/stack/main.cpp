#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
    int max = 100;
    int i;

    for (i=0; i<max; i++) {
        try {
            Stack::push(i);
        }
        catch (Stack::Overflow()) {
            std::cout << "overflow detected, terminate\n";
            exit(1);
        }
    }

    for (i=max-1; i>=0; i--) {
        if (Stack::pop() != i)
           std::cout << "impossible\n";
    }

    std::cout << "Done\n";
}
