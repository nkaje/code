#include "stack.h"
#include <list>
using namespace std;

class List_stack : public Stack {
    list<int> lc;
public:
    List_stack() { };
    ~List_stack() { };
    void push(int in)
    {
        lc.push_front(in);
    }
    int pop();
};

