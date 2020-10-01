#include "uarray2.h"
#include <stdio.h>

int main()
{
        UArray2_T arr = UArray2_new(9,9,4);
        int *ptr = UArray2_at(arr, 0, 0);
        *ptr = 2;
        int *ptr2 = UArray2_at(arr, 0, 0);
        printf("%d\n", *ptr2);
        int width = UArray2_width(arr);
        int height = UArray2_height(arr);
        int size = UArray2_size(arr);
        printf("width: %d height: %d size: %d", width, height, size);
        UArray2_free(&arr);
}
