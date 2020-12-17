#include <stdio.h>
#include <stdlib.h>

int *merge_sorted(int *arr_one, int len_one, int *arr_two, int len_two, int *reslength)
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
    int i;
    int res_length;

    int *merged = merge_sorted(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), &res_length);

    for (i=0; i<res_length; i++) {
        printf("%d,", merged[i]);
    }
    printf("\n");
    free(merged);
    return 0;
}
