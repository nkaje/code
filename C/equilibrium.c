#include <stdio.h>

void equilibrium(int *arr, int size)
{
	int i;
    int R = 0;
    int L = 0;
    int S = 0;

	/* Sum total of the array */
	for (i = 0; i < size; i++) {
        S += *(arr + i);
    }

    for (i=0; i<size; i++) {
        /* If it is first or last element, we know it already */
        if (i == 0) {
            L = 0;
            R = (S - (*(arr + i)));
        } else if (i == size-1) {
            R = 0;
            L = (S - (*(arr + i)));
        } else {
            /* Left side gets the last but one element (when last but one convention applies, i.e doesn't apply for 0
             * index)
             * Right side is just Sum - Current Left and the element we are on
             */
            L += *(arr + i-1);
            R = (S - (L + *(arr + i)));
        }

        if (L == R) {
            printf("%d,", i);
        }

    }

    printf("\n");
    return;
 }

 int main()
 {
     /* Test cases */
     int arr_easy[] = {0, 1, 0};
     int arr[] = {0, -3, 5, -4, -2, 3, 1, 0};
     int arr_a[] = {0, -1, 4, -4, -1, 3, 1, 0};
     int arr_b[] = {0, -1, 0, 5, 0, 0, -1, 0};
     int arr_1size[] = {10};
     int arr_2size[] = {1, 1};

     equilibrium(arr_easy, sizeof(arr_easy)/sizeof(arr_easy[0]));
     equilibrium(arr, sizeof(arr)/sizeof(arr[0]));
     equilibrium(arr_a, sizeof(arr_a)/sizeof(arr_a[0]));
     equilibrium(arr_b, sizeof(arr_b)/sizeof(arr_a[0]));

     equilibrium(arr_1size, sizeof(arr_1size)/sizeof(arr_1size[0]));
     equilibrium(arr_2size, sizeof(arr_2size)/sizeof(arr_2size[0]));
     return 0;
 }
