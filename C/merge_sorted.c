#include <stdio.h>
#include <stdlib.h>

int *merge_sorted(const int *arr_one, const int len_one, const int *arr_two, const int len_two, int *reslength)
{
    int a_idx, b_idx;
    int *result = malloc(sizeof(int) * (len_one + len_two));
    int i;


    if (result == NULL)
       return NULL;

    for (a_idx = 0, b_idx = 0, i = 0; ((a_idx < len_one) && (b_idx < len_two)); i++) {
        if (arr_one[a_idx] < arr_two[b_idx]) {
            result[i] = arr_one[a_idx];
            a_idx++;
        } else {
            result[i] = arr_two[b_idx];
            b_idx++;
        }
    }

    if (a_idx >= len_one) {
        while(b_idx < len_two) {
            result[i++] = arr_two[b_idx++];
        }
    } else if (b_idx >= len_two) {
        while(a_idx < len_one) {
            result[i++] = arr_one[a_idx++];
        }
    }

    *reslength = (len_one + len_two);
    return result;
}

int main()
{
    int b[] = {1, 2, 3, 4};
    int a[] = {1, 2, 3, 4};

    int c[] = {1, 2, 3, 4};
    int d[] = {10};

    int e[] = {1, 2, 3, 4};
    int f[] = {-1};

    int g[] = {1, 2, 3, 4};
    int h[] = {101};

    int i;
    int res_length;

    /******************** test 1 *****************/
    int *merged = merge_sorted(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), &res_length);

    for (i=0; i<res_length; i++) {
        printf("%d,", merged[i]);
    }
    printf("\n");
    free(merged);

    /******************** test 2 *****************/
    merged = merge_sorted(c, sizeof(c)/sizeof(c[0]), d, sizeof(d)/sizeof(d[0]), &res_length);

    for (i=0; i<res_length; i++) {
        printf("%d,", merged[i]);
    }
    printf("\n");
    free(merged);

    /******************** test 3 *****************/
    merged = merge_sorted(e, sizeof(e)/sizeof(e[0]), f, sizeof(f)/sizeof(f[0]), &res_length);

    for (i=0; i<res_length; i++) {
        printf("%d,", merged[i]);
    }
    printf("\n");
    free(merged);

    /******************** test 4 *****************/
    merged = merge_sorted(g, sizeof(g)/sizeof(g[0]), h, sizeof(h)/sizeof(h[0]), &res_length);

    for (i=0; i<res_length; i++) {
        printf("%d,", merged[i]);
    }
    printf("\n");
    free(merged);

    /******************** test 5 *****************/
    merged = merge_sorted(g, sizeof(g)/sizeof(g[0]), NULL, 0, &res_length);

    for (i=0; i<res_length; i++) {
        printf("%d,", merged[i]);
    }
    printf("\n");
    free(merged);

    /******************** test 6 *****************/
    merged = merge_sorted(NULL, 0, NULL, 0, &res_length);

    for (i=0; i<res_length; i++) {
        printf("%d,", merged[i]);
    }
    printf("\n");
    free(merged);

    return 0;
}
