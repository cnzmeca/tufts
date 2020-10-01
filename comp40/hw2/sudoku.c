/*
 * sudoku.c
 * by Christian Zinck and Joshua Mitchell. Date due 2/12/18
 * Homework 2: iii
 *
 * A program that exits with a code of 1 for an invalid sudoku solution and
 * with a code of 0 for a valid sudoku solution.
 */

#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include <pnmrdr.h>

// Function prototyrpes
UArray2_T pgmread (FILE *inputfp);
void has_duplicates(int arr[]);
void check_rows(UArray2_T graymap);
void check_cols(UArray2_T graymap);
void check_boxes(UArray2_T graymap);
void check_solution(UArray2_T graymap);

int main(int argc, char *argv[])
{
        UArray2_T graymap;

        if (argc == 2) {
                char *filename = argv[1];
                FILE *fp = fopen(filename, "rb");
                if (fp == NULL) {
                        fprintf(stderr, "Invalid file name. \n");
                        exit(EXIT_FAILURE);
                }

                graymap = pgmread(fp);
                fclose(fp);
                check_solution(graymap);
        } else if (argc == 1) {
                graymap = pgmread(stdin);
                check_solution(graymap);
        } else {
                fprintf(stderr, "Too many command line arguments\n");
                exit(EXIT_FAILURE);
        }

        UArray2_free(&graymap);
}

/*
 * pgmread takes and reads a stream, and if it contains a 9x9 pgm image,
 * stores the data from the file in a UArray2_T, which it then returns.
 *
 * Parameters:
 *         inputfp: The stream to read from.
 */
UArray2_T pgmread (FILE *inputfp)
{
        Pnmrdr_T rdr = Pnmrdr_new(inputfp);
        Pnmrdr_mapdata data = Pnmrdr_data(rdr);
 
        if (data.width != 9 || data.height != 9) {
                fprintf(stderr, "Incorrect Dimensions. Expected 9x9.\n");
                exit(EXIT_FAILURE);
        }

        UArray2_T graymap = UArray2_new(data.width, data.height, 4);


        for (unsigned i = 0; i < data.height; i++) {
                for (unsigned j = 0; j < data.width; j++) {
                        *((int *)UArray2_at(graymap, j, i)) = Pnmrdr_get(rdr);
                }
        }

        Pnmrdr_free(&rdr);
        return graymap;
}

/*
 * has_duplicates takes an integer array and checks if there are any duplicate
 * values in the array. If there are any duplicates, has_duplicates exits the
 * program with EXIT_FAILURE.
 *
 * Parameters:
 *         arr: The array to check for duplicate values.
 */
void has_duplicates(int arr[])
{
        int counter[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

        for (int i = 0; i < 9; i++) {
                counter[arr[i] - 1]++;
                if (counter[arr[i] - 1] == 2) {
                        exit(EXIT_FAILURE);
                }
        }
}

/*
 * check_rows takes a UArray2_T and checks if there are duplicates in any of
 * its rows. If a duplicate is found, it exits the program.
 *
 * Parameters:
 *         graymap: The UArray2_T to check for duplicates in its rows.
 */
void check_rows(UArray2_T graymap)
{
        for (int i = 0;  i < 9; i++) {
                int arr[9];
                for (int j = 0; j < 9; j++) {
                        arr[j] = *((int *)UArray2_at(graymap, j, i));
                }
                has_duplicates(arr);
        }
}

/*
 * check_cols takes a UArray2_T and checks if there are duplicates in any of
 * its columns. If a duplicate is found, it exits the program.
 *
 * Parameters:
 *         graymap: The UArray2_T to check for duplicates in its columns.
 */
void check_cols(UArray2_T graymap)
{
        for (int i = 0;  i < 9; i++) {
                int arr[9];
                for (int j = 0; j < 9; j++) {
                        arr[j] = *((int *)UArray2_at(graymap, i, j));
                }
                has_duplicates(arr);
        }
}

/*
 * check_boxes takes a UArray2_T and checks if there are duplicates in any of
 * its 3x3 boxes. If a duplicate is found, it exits the program.
 *
 * Parameters:
 *         graymap: The UArray2_T to check for duplicates in its boxes.
 */
void check_boxes(UArray2_T graymap)
{
        for (int i = 0; i < 9; i+=3) {
                for (int j = 0; j < 9; j+=3) {
                        int arr[9];
                        for (int k = 0; k < 3; k++) {
                                for (int l = 0; l < 3; l++) {
                                        arr[3 * k + l] = 
                                        *((int *)UArray2_at(graymap,
                                        i + k, j + l));
                                }
                        }
                        has_duplicates(arr);
                }
        }
}

/*
 * check_solution takes a UArray2_T and checks if it is a valid sudoku
 * solution. If it isn't it exits the program.
 *
 * Parameters:
 *         graymap: The UArray2_T to check for a valid solution.
 */
void check_solution(UArray2_T graymap)
{
        check_rows(graymap);
        check_cols(graymap);
        check_boxes(graymap);
}
