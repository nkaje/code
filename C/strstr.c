#include <stdio.h>
#include <string.h>


char *strchr_custom(char *s, register char c)
{
    if (s == NULL)
        return s;

    while (*s != '\0') {
        if (*s == c)
            return s;
        else
            s++;
    }

    return NULL;
}

char *strstr_custom(char *haystack, const char *needle)
{
    char *ret = NULL;

    for(; (ret = strchr_custom(haystack, *needle)) != NULL; haystack++) {
        if (0 == strncmp(haystack, needle, strlen(needle))) {
            return haystack;
        }
    }

    return NULL;
}

int main()
{
    char *needle = "findme";
    char *haystack = "fffoundmeeee";
    char *ret = NULL;

    /* test */
    ret = strstr_custom(haystack, needle);
    if (ret != NULL) {
        printf("found at offset %ld, %s\n", ret - haystack, ret);
    } else {
        printf("%s not found in %s\n", needle, haystack);
    }

    /* verify with std implementation */
    ret = strstr(haystack, needle);
    if (ret != NULL) {
        printf("found at offset %ld, %s\n", ret - haystack, ret);
    } else {
        printf("%s not found in %s\n", needle, haystack);
    }
    return 0;
}
