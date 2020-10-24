#include <stdio.h>
#include <string.h>

char *end_of_delim(char *str, const char *delim)
{
    int i;
    char *tmp, *prev_max = NULL;

    for(i=0; *(delim + i) != '\0'; i++) {
        tmp = strchr(str, *(delim + i));
        if (tmp > prev_max) {
            prev_max = tmp;
        }
    }
    /* point to one after the last delimiter */
    return prev_max + 1;
}

char *strtok_custom(char *str, const char *delim)
{
    static char *save;
    int i;
    /* end of current search */
    char *eoc = NULL;
    /* pointer to return after updating static pointer */
    char *tmp = NULL;

    if (str == NULL && save == NULL)
        return NULL;

    if (str != NULL)
        save = str;

    for (i = 0; *(delim + i) != '\0'; i++) {
        tmp = save;
        eoc = strchr((save), *(delim + i));
        if (eoc != NULL) {
            /* Update saved offset to beginning of next seq */
            save = end_of_delim(eoc, delim);
            *eoc = '\0';
            return tmp;
        } 
    }
    return tmp;
}

int main()
{
    char str[] = "ABCD;/EFGH;/VRFX";
    char *delim = ";/";
    char *res = NULL;

    res = strtok_custom(str, delim);
    printf("strtok_custom call 1 %s\n", res);

    res = strtok_custom(NULL, delim);
    printf("strtok_custom call 2 %s\n", res);
    
    res = strtok_custom(NULL, delim);
    printf("strtok_custom call 3 %s\n", res);
    return 0;
}
