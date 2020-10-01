#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"

typedef struct T *T;

struct UArray2_T {
        int height;
        int width;
        int elem_size;
        UArray_T u_arr;        
};

/*
 * UArray2_new creates and returns a new UArray2 with the given dimension 
 * sizes containing elements of the given element size.
 *
 * Parameters:
 *      COLS: The width of the 2D array
 *      ROWS: The height of the 2D array
 *      ELEM_SIZE: The size of the elements contained in the array 
 */
extern UArray2_T UArray2_new(int COLS, int ROWS, int ELEM_SIZE)
{
        if (COLS > 0 && ROWS > 0 && ELEM_SIZE > 0) {
                struct UArray2_T *arr = malloc(sizeof(*arr));
                arr->width = COLS;
                arr->height = ROWS;
                arr->elem_size = ELEM_SIZE;
                arr->u_arr = UArray_new(COLS * ROWS, ELEM_SIZE);
                return arr;
        } else {
                fprintf(stderr, "Dimensions and size must be positive\n");
                return NULL;
        }
}

/*
 * UArray2_at takes a UArray2_T, a column number, and a row number, and
 * returns a reference to the element located at the given column and row
 * number.
 *
 * Parameters:
 *         arr: The UArray2_T containing the desired element
 *         col: The column number of the desired element
 *         row: The row number of the desired element
 */
extern void *UArray2_at(UArray2_T arr, int col, int row)
{
        if (row >= 0 && row < arr->height && col >= 0 && col < arr->width) {
                return UArray_at(arr->u_arr, get_1D_pos(arr, col, row));
        } else {
                fprintf(stderr, "Index out of bounds.\n");
                return NULL;
        }
}

/*
 * UArray2_map_row_major takes a UArray2_T, a pointer to an apply function,
 * and a void pointer, and performs the apply function on every value in the
 * array in row major order.
 *
 * arr: The UArray2_T that is to be mapped
 * apply: The apply function that is to be performed on each value
 * cl: A void pointer to anything extra that is to be included
 */
extern void UArray2_map_row_major(UArray2_T arr, void apply(int DIM1, int DIM2,
        UArray2_T arr, void *value, void *cl), void *cl)
{
        for (int r = 0; r < arr->height; r++) {
                for (int c = 0; c < arr->width; c++) {
                        void *val = UArray2_at(arr, c, r);
                        apply(c, r, arr, val, cl);
                }
        }
}


/*
 * UArray2_map_col_major takes a UArray2_T, a pointer to an apply function,
 * and a void pointer, and performs the apply function on every value in the
 * array in column major order.
 *
 * arr: The UArray2_T that is to be mapped
 * apply: The apply function that is to be performed on each value
 * cl: A void pointer to anything extra that is to be included
 */
extern void UArray2_map_col_major(UArray2_T arr, void apply(int DIM1, int DIM2,
        UArray2_T arr, void *value, void *cl), void *cl)
{
        for (int c = 0; c < arr->width; c++) {
                for (int r = 0; r < arr->height; r++) {
                        void *val = UArray2_at(arr, c, r);
                        apply(c, r, arr, val, cl);
                }
        }
}

/*
 * UArray2_free frees the memory allocated for the given UArray2_T.
 *
 * Parameters:
 *         arr: A UArray2_T pointer to be freed 
 */
extern void UArray2_free(UArray2_T *arr)
{
        UArray_free(&((*arr)->u_arr));
        free(*arr);
}

/*
 * UArray2_height takes an UArray2_T and returns it's height.
 *
 * Parameters:
 *         arr: The UArray2_T from which to return the height
 */
extern int UArray2_height(UArray2_T arr)
{
        return arr->height;
}

/*
 * UArray2_width takes an UArray2_T and returns it's width.
 *
 * Parameters:
 *         arr: The UArray2_T from which to return the width
 */
extern int UArray2_width(UArray2_T arr)
{
        return arr->width;
}

/*
 * UArray2_size takes an UArray2_T and returns the size of it's elements.
 *
 * Parameters:
 *         arr: The UArray2_T from which to return the element size
 */
extern int UArray2_size(UArray2_T arr)
{
        return arr->elem_size;
}

/*
 * get_1D_pos takes a UArray2_T, a column number, and a row number, and
 * returns the position in the 1D array.
 *
 * Parameters:
 *         arr: The UArray2_T
 *         col: The column number
 *         row: The row number
 */
int get_1D_pos(UArray2_T arr, int col, int row)
{
        return ((col) * arr->height) + row;
}
