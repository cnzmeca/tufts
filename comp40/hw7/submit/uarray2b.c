/* uarray2b.c
 * by Joshua Mitchell & Christian Zinck 2/22/18
 * HW3: Locality
 * 
 * The implementation for the uarray2b interface.
 */

#include "uarray2b.h"
#include "assert.h"
#include "uarray.h"
#include "uarray2.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define T UArray2b_T

struct T {
        UArray2_T blocks;
        int width, height, size, blocksize;
};

/*
 * UArray2b_new creates and returns a new UArray2b_T with the given dimensions 
 * containing elements of the given element size in blocks of the given block
 * size.
 *
 * Parameters:
 *      width: The width of the 2D array
 *      height: The height of the 2D array
 *      size: The size of the elements contained in the array
 *      blocksize: The side length in cells of a block in the array
 */
extern T UArray2b_new (int width, int height, int size, int blocksize)
{
        T b_array = malloc(sizeof(*b_array));
        b_array->width = width;
        b_array->height = height;
        b_array->size = size;
        b_array->blocksize = blocksize;
       
        
        assert(blocksize >= 1); 

        int b_width;
        if (blocksize >= width) {
                b_width = 1;
        } else {
                b_width = (width + blocksize - 1) / blocksize;
        }

        int b_height;
        if (blocksize >= height) {
                b_height = 1;
        } else {
                b_height = (height + blocksize - 1) / blocksize;
        }

        b_array->blocks = UArray2_new(b_width, b_height, size);
        for (int c = 0; c < b_width; c++) {
                for (int r = 0; r < b_height; r++) {
                        UArray_T *block = UArray2_at(b_array->blocks, c, r);
                        *block = UArray_new(blocksize * blocksize, size);
                }
        }
        return b_array;
}

/*
 * UArray2b_new_64K_block creates and returns a new UArray2b_T with the given
 * dimensions containing elements of the given element size in blocks of at most
 * 64K with blocksize maximized.
 *
 * Parameters:
 *      width: The width of the 2D array
 *      height: The height of the 2D array
 *      size: The size of the elements contained in the array
 */
extern T UArray2b_new_64K_block(int width, int height, int size)
{
        int blocksize;
        if (size >= 65536) {
                blocksize = 1;
        } else {
                blocksize = (int)(sqrt(65536 / size));
        }
        return UArray2b_new (width, height, size, blocksize);
}

/*
 * UArray2b_free frees the memory allocated for the given UArray2b_T.
 *
 * Parameters:
 *         array2b: A UArray2b_T pointer to be freed 
 */
extern void UArray2b_free (T *array2b){
        assert(array2b && *array2b);
        for (int c = 0; c < UArray2_width((*array2b)->blocks); c++) {
                for (int r = 0; r < UArray2_height((*array2b)->blocks); r++) {
                        UArray_free(UArray2_at((*array2b)->blocks, c, r));
                }
        }
        UArray2_free(&((*array2b)->blocks));
        free(*array2b);
}

/*
 * UArray2b_width takes an UArray2b_T and returns it's width.
 *
 * Parameters:
 *         array2b: The UArray2b_T from which to return the width
 */
extern int UArray2b_width(T array2b)
{
        assert(array2b);
        return array2b->width;
}

/*
 * UArray2b_height takes an UArray2b_T and returns it's height.
 *
 * Parameters:
 *         array2b: The UArray2b_T from which to return the height
 */
extern int UArray2b_height(T array2b)
{
        assert(array2b);
        return array2b->height;
}

/*
 * UArray2b_size takes an UArray2b_T and returns the size of it's elements.
 *
 * Parameters:
 *         array2b: The UArray2b_T from which to return the element size
 */
extern int UArray2b_size(T array2b)
{
        assert(array2b);
        return array2b->size;
}

/*
 * UArray2b_blocksize takes an UArray2b_T and returns the size of a block.
 *
 * Parameters:
 *         array2b: The UArray2b_T from which to return the blocksize
 */
extern int UArray2b_blocksize(T array2b)
{
        assert(array2b);
        return array2b->blocksize;
}

/*
 * UArray2b_at takes a UArray2b_T, a column number, and a row number, and
 * returns a reference to the element located at the given column and row
 * number.
 *
 * Parameters:
 *         array2b: The UArray2b_T containing the desired element
 *         c: The column number of the desired element
 *         r: The row number of the desired element
 */
extern void *UArray2b_at(T array2b, int c, int r)
{
        assert(array2b);
        int b_size = array2b->blocksize;
        UArray_T *block = UArray2_at(array2b->blocks, c / b_size, r / b_size);
        return UArray_at(*block, b_size * (c % b_size) + (r % b_size));
        
}

/*
 * UArray2b_map takes a UArray2b_T, a pointer to an apply function, and a void
 * pointer, and performs the apply function on every value in the array in block
 * major order.
 *
 * array2b: The UArray2b_T that is to be mapped
 * apply: The apply function that is to be performed on each value
 * cl: A void pointer to anything extra that is to be included
 */
extern void UArray2b_map(T array2b, void apply(int col, int row, T array2b,
                         void *elem, void *cl), void *cl)
{
        assert(array2b);
        int b_size = array2b->blocksize;
        for (int r1 = 0; r1 < UArray2_height(array2b->blocks); r1++) {
                for (int c1 = 0; c1 < UArray2_width(array2b->blocks); c1++) {
                        for (int r2 = 0; r2 < b_size; r2++) {
                                for (int c2 = 0; c2 < b_size; c2++) {
                                        int column = c1 * b_size + c2;
                                        int row = r1 * b_size + r2;
                                        void *val = UArray2b_at(array2b, column,
                                                                row);
                                        if (column < UArray2b_width(array2b) &&
                                            row < UArray2b_height(array2b)) {
                                                apply(column, row, array2b,
                                                      val, cl);
                                        }
                                }
                        }
                }
        }
}
#undef T
