#include "uarray2b.h"
#include <stdio.h>
int main(void)
{
        UArray2b_T arr = UArray2b_new_64K_block(18, 180, 8);
        int *ptr = UArray2b_at(arr, 0, 0);
        *ptr = 5;
        int *ptr2 = UArray2b_at(arr, 0, 0);
        fprintf(stderr, "%d\n", *ptr2);
        UArray2b_free(&arr);
}
