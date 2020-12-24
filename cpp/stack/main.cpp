#include "stack.h"
#include "array_stack.h"
#include "list_stack.h"
#include <iostream>

#define LIMIT 20
using namespace std;

void f(Stack &s_ref)
{
    int in;
    int out;


    for (int i=0; i<LIMIT; i++) {
        in = i;
        s_ref.push(in);
        out = s_ref.pop();
        if (out != in)
            throw Stack::Mismatch();
        else
            cout << "reading out " << out << "\n";
    }

    for (int i=0; i<LIMIT; i++) {
        in = i;
        s_ref.push(in);
    }
    for (int i=0; i<LIMIT; i++) {
        out = s_ref.pop();
        if (out != (LIMIT - i - 1)) {
            cout << "index " << i << "\n";
            throw Stack::Mismatch();
        } else {
            cout << "reading out " << out << "\n";
        }
    }
}

int main()
{
    Array_stack as(LIMIT);
    List_stack ls;
    cout << "type: Array begin\n";
    f(as);
    cout << "type: Array end\n";
    cout << "type: List begin\n";
    f(ls);
    cout << "type: List end\n";
}
