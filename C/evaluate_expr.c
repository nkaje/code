#include <stdio.h>
#include <string.h>

int atoi(const char *str)
{
    int out = 0;

    while(*str) {
        if (!(*str >= '0') && (*str <= 9)) {
            return -1;
        }
        out *= 10;
        out += (*str++ - '0');
    }
    return out;
}

/*
 * Evaluate: *s are evaluated first
 */
int evaluate(char *str)
{
    char *inner, *outer;
    int sum = 0;
    int mult;
    char *pi, *po;

    if (!str)
        return 0;

    outer = str;
    po = strtok_r(str, "+", &outer);
    while(po) {
        mult = 1;
        inner = po;
        pi = strtok_r(po, "*", &inner);
        while(pi) {
            mult *= atoi(pi);
            pi = strtok_r(NULL, "*", &inner);
        }
        sum += mult;
        po = strtok_r(NULL, "+", &outer);
    }
    return sum;
}

int main()
{
    char ev[] = "1+20*2+1"; /* should be 42 */

    printf("%d\n", evaluate(ev));
    printf("%d\n", evaluate(NULL));
    return 0;
}
