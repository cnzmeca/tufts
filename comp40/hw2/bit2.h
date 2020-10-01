/*
 * bit2.h
 * by Joshua Mitchell & Christian Zinck 2/6/18
 * HW2: iii
 * 
 * The interface for the bit2 implementation.
 */

#ifndef BIT2_H_
#define BIT2_H_

typedef struct Bit2_T *Bit2_T;

extern Bit2_T Bit2_new(int COLS, int ROWS);

extern int Bit2_get(Bit2_T arr, int col, int row);

extern int Bit2_put(Bit2_T arr, int col, int row, int value);

extern void Bit2_map_row_major(Bit2_T arr, void apply(int col, int row,
   Bit2_T arr, int value, void *cl), void *cl);

extern void Bit2_map_col_major(Bit2_T arr, void apply(int col, int row,
   Bit2_T arr, int value, void *cl), void *cl);

extern void Bit2_free(Bit2_T *arr);

extern int Bit2_height(Bit2_T arr);

extern int Bit2_width(Bit2_T arr);

int get_1D_pos(Bit2_T arr, int col, int row);

#endif
