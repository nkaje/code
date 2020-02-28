#include <stdio.h>
#include "example.h"

enum {
    ERROR = 0,
    ERROR_ONE,
    ERROR_TWO,
    ERROR_THREE,
    ERROR_MAX
};

int print_error()
{
    return ERROR_THREE;
}

int main()
{
//    printf("Example %d", EXAMPLE_DEFINE);
    print_error();
    return 0;
}

