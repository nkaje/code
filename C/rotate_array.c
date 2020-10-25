#include <stdio.h>

#define SIZEOFARRAY(x) (sizeof((x))/sizeof((x[0])))

void r_l_once(int *array, int size)
{
    int temp = array[0];
    int i;

    for(i=0; i<size-1; i++)
        array[i] = array[i+1];

    array[i] = temp;
}

void rotate_l_array(int *array, int d, int size)
{
    int i;
    d %= size;

    for(i=0; i<d; i++)
        r_l_once(array, size);
}

void r_r_once(int *array, int size)
{
    int temp = array[size-1];
    int i;

    for (i=size-1; i>0; i--)
        array[i] = array[i-1];

    array[i] = temp;
}

void rotate_r_array(int *array, int d, int size)
{
    int i;
    d %= size;

    for(i=0; i<d; i++)
        r_r_once(array, size);
}

void print_array(int *array, int size)
{
    int i;

    for (i=0; i<size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    int array[] = {1, 2, 3, 4, 5};
    int d = 2;

    print_array(array, SIZEOFARRAY(array));
    rotate_l_array(array, d, SIZEOFARRAY(array));
    print_array(array, SIZEOFARRAY(array));

    rotate_r_array(array, d, SIZEOFARRAY(array));
    print_array(array, SIZEOFARRAY(array));
    return 0;
}
