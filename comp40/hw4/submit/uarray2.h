#ifndef UARRAY2_H_
#define UARRAY2_H_

#include <uarray.h>

typedef struct UArray2_T *UArray2_T;

extern UArray2_T UArray2_new(int COLS, int ROWS, int ELEM_SIZE);

extern void *UArray2_at(UArray2_T arr, int col, int row);

extern void UArray2_map_row_major(UArray2_T arr, void apply(int col, int row,
        UArray2_T arr, void *value, void *cl), void *cl);

extern void UArray2_map_col_major(UArray2_T arr, void apply(int col, int row,
        UArray2_T arr, void *value, void *cl), void *cl);

extern void UArray2_free(UArray2_T *arr);

extern int UArray2_height(UArray2_T arr);

extern int UArray2_width(UArray2_T arr);

extern int UArray2_size(UArray2_T arr);

int get_1D_pos(UArray2_T arr, int col, int row);

#endif
