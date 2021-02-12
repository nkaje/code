#include <stdio.h>

void foo(void);
void call(void);

void __wrap_foo(void)
{
    printf("In __wrap_foo\n");
    foo();
}

void foo(void)
{
    printf("In foo\n");
}

int main()
{
    call();
    return 0;
}
