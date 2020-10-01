/*
 * a2plain.c
 * by Christian Zinck and Josh Mitchell. 2/22/18
 * HW 3: Locality
 *
 * A program that implements the UArray2 half of the polymorphic interface
 * A2Methods. This interface allows a user to perform operations on a 2D array,
 * whether it is a UArray2 or UArray2b.
 */
#include <stdlib.h>
#include <a2plain.h>
#include "uarray2.h"

#define A2 A2Methods_UArray2

/*
 * new creates and returns a new A2Methods_UArray2 with the given dimensions 
 * containing elements of the given element size in blocks of the given block
 * size.
 *
 * Parameters:
 *      width: The width of the 2D array
 *      height: The height of the 2D array
 *      size: The size of the elements contained in the array
 */
static A2 new(int width, int height, int size)
{
        return UArray2_new(width, height, size);
}

/*
 * new_with_blocksize creates and returns a new A2Methods_UArray2 with the given
 * dimensions containing elements of the given element size in blocks of the
 * given blocksize.
 *
 * Parameters:
 *      width: The width of the 2D array
 *      height: The height of the 2D array
 *      size: The size of the elements contained in the array
 *      blocksize: The side length in cells of a block in the array
 */
static A2 new_with_blocksize(int width, int height, int size,
                                            int blocksize)
{
        (void) blocksize;
        return UArray2_new(width, height, size);
}

/*
 * a2free frees the memory allocated for the given A2Methods_UArray2.
 *
 * Parameters:
 *         array2p: An A2Methods_UArray2 pointer to be freed 
 */
static void a2free(A2 *array2p)
{
        UArray2_free((UArray2_T *) array2p);
}

/*
 * width takes an A2Methods_UArray2 and returns it's width.
 *
 * Parameters:
 *         array2: The A2Methods_UArray2 from which to return the width
 */
static int width(A2 array2)
{
        return UArray2_width(array2);
}

/*
 * height takes an A2Methods_UArray2 and returns it's height.
 *
 * Parameters:
 *         array2: The A2Methods_UArray2 from which to return the height
 */
static int height(A2 array2)
{
        return UArray2_height(array2);
}

/*
 * size takes an A2Methods_UArray2 and returns it's size.
 *
 * Parameters:
 *         array2: The A2Methods_UArray2 from which to return the size
 */
static int size(A2 array2)
{
        return UArray2_size(array2);
}

/*
 * blocksize takes an A2Methods_UArray2 and returns it's blocksize.
 *
 * Parameters: 
 *         array2: The A2Methods_UArray2 from which to return the blocksize
 */
static int blocksize(A2 array2)
{
        (void) array2;
        return 1;
}

/*
 * at takes a A2Methods_UArray2, a column number, and a row number, and
 * returns a reference to the element located at the given column and row
 * number.
 *
 * Parameters:
 *         array2: The UArray2b_T containing the desired element
 *         i: The column number of the desired element
 *         j: The row number of the desired element
 */
static A2Methods_Object *at(A2 array2, int i, int j)
{
        return UArray2_at(array2, i, j);
}

typedef void applyfun(int i, int j, UArray2_T array2, void *elem, void *cl);

/*
 * map_row_major takes a A2Methods_UArray2, a pointer to an apply function,
 * and a void pointer, and performs the apply function on every value in the
 * array in row major order.
 *
 * array2: The A2Methods_UArray2 that is to be mapped
 * apply: The apply function that is to be performed on each value
 * cl: A void pointer to anything extra that is to be included
 */
static void map_row_major(A2 array2, A2Methods_applyfun apply, void *cl)
{
        UArray2_map_row_major(array2, (applyfun *) apply, cl);
}

/*
 * map_col_major takes a A2Methods_UArray2, a pointer to an apply function,
 * and a void pointer, and performs the apply function on every value in the
 * array in column major order.
 *
 * array2: The A2Methods_UArray2 that is to be mapped
 * apply: The apply function that is to be performed on each value
 * cl: A void pointer to anything extra that is to be included
 */
static void map_col_major(A2 array2, A2Methods_applyfun apply, void *cl)
{
        UArray2_map_col_major(array2, (applyfun *) apply, cl);
}

struct small_closure {
        A2Methods_smallapplyfun *apply;
        void *cl;
};

static void apply_small(int i, int j, UArray2_T array2, void *elem, void *vcl)
{
        struct small_closure *cl = vcl;
        (void)i;
        (void)j;
        (void)array2;
        cl->apply(elem, cl->cl);
}

static void small_map_row_major(A2 a2, A2Methods_smallapplyfun apply,
                                  void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_row_major(a2, apply_small, &mycl);
}

static void small_map_col_major(A2 a2, A2Methods_smallapplyfun apply,
                                  void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_col_major(a2, apply_small, &mycl);
}

static struct A2Methods_T uarray2_methods_plain_struct = {
        new,
        new_with_blocksize,
        a2free,
        width,
        height,
        size,
        blocksize,
        at,
        map_row_major,
        map_col_major,
        NULL,
        map_row_major,
        small_map_row_major,
        small_map_col_major,
        NULL,
        small_map_row_major,
};

        A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;
