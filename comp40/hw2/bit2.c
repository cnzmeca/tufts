#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "bit.h"

struct Bit2_T {
        int height;
        int width;
        Bit_T vec;
};

/*
 * Bit2_new creates and returns a new Bit2 with the given dimension 
 * sizes containing bits.
 *
 * Parameters:
 *         COLS: The width of the 2D array
 *         ROWS: The height of the 2D array
 */
extern Bit2_T Bit2_new(int COLS, int ROWS)
{
        if (COLS > 0 && ROWS > 0) {
                struct Bit2_T *arr = malloc(sizeof(*arr));
                arr->width = COLS;
                arr->height = ROWS;
                arr->vec = Bit_new(COLS * ROWS);
                return arr;       
        } else {
                fprintf(stderr, "Dimensions must be positive\n");
                return NULL;
        }
}

/*
 * Bit2_get takes a Bit2_T, a column number, and a row number, and returns
 * the bit located at the given position.
 *
 * Parameters:
 *         arr: The BIt2_T from which a bit is to be retrieved
 *         col: The column number
 *         row: The row number
 */
extern int Bit2_get(Bit2_T arr, int col, int row)
{
        if (row >= 0 && row < arr->height && col >= 0 && col < arr->width) {
                return Bit_get(arr->vec, get_1D_pos(arr, col, row));
        } else {
                fprintf(stderr, "Index out of bounds.\n");
                return -1;
        }


}

/*
 * Bit2_put takes a Bit2_T, a column number, a row number, and a value, and
 * puts the value in the given position and returns the previous value in
 * that position.
 *
 * Parameters:
 *         arr: The BIt2_T from which a bit is to be changed
 *         col: The column number
 *         row: The row number
 *         value: The new value to put in the array
 */
extern int Bit2_put(Bit2_T arr, int col, int row, int value)
{
        if (row >= 0 && row < arr->height && col >= 0 && col < arr->width) { 
                return Bit_put(arr->vec, get_1D_pos(arr, col, row), value);
        } else {
                fprintf(stderr, "Index out of bounds.\n");
                return -1;
        }
}

/*
 * Bit2_map_row_major takes a Bit2_T, a pointer to an apply function,
 * and a void pointer, and performs the apply function on every value in the
 * array in row major order.
 *
 * arr: The Bit2_T that is to be mapped
 * apply: The apply function that is to be performed on each value
 * cl: A void pointer to anything extra that is to be included
 */
extern void Bit2_map_row_major(Bit2_T arr, void apply(int col, int row,
        Bit2_T arr, int value, void *cl), void *cl)
{
        for (int r = 0; r < arr->height; r++) {
                for (int c = 0; c < arr->width; c++) {
                        int val = Bit2_get(arr, c, r);
                        apply(c, r, arr, val, cl);
                }
        }
}


/*
 * Bit2_map_col_major takes a Bit2_T, a pointer to an apply function,
 * and a void pointer, and performs the apply function on every value in the
 * array in column major order.
 *
 * arr: The Bit2_T that is to be mapped
 * apply: The apply function that is to be performed on each value
 * cl: A void pointer to anything extra that is to be included
 */
extern void Bit2_map_col_major(Bit2_T arr, void apply(int col, int row,
        Bit2_T arr, int value, void *cl), void *cl)
{
        for (int c = 0; c < arr->width; c++) {
                for (int r = 0; r < arr->height; r++) {
                        int val = Bit2_get(arr, c, r);
                        apply(c, r, arr, val, cl);
                }
        }
}

/*
 * Bit2_free frees the memory allocated for the given Bit2_T.
 *
 * Parameters:
 *         arr: A Bit2_T pointer to be freed 
 */
extern void Bit2_free(Bit2_T *arr)
{
        Bit_free(&((*arr)->vec));
        free(*arr);
}

/*
 * Bit2_height takes an Bit2_T and returns it's height.
 *
 * Parameters:
 *         arr: The Bit2_T from which to return the height
 */
extern int Bit2_height(Bit2_T arr)
{
        return arr->height;
}

/*
 * Bit2_width takes an Bit2_T and returns it's width.
 *
 * Parameters:
 *         arr: The Bit2_T from which to return the width
 */
extern int Bit2_width(Bit2_T arr)
{
        return arr->width;
}

/*
 * get_1D_pos takes a Bit2_T, a column number, and a row number, and
 * returns the position in the 1D array.
 *
 * Parameters:
 *         arr: The Bit2_T
 *         col: The column number
 *         row: The row number
 */
int get_1D_pos(Bit2_T arr, int col, int row)
{
        return ((col) * arr->height) + row;
}
