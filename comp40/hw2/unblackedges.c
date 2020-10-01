/*
 * unblackedges.c
 * by Christian Zinck and Joshua Mitchell. 2/12/18
 * Homework 2: iii
 *
 * A program that prints on standard output a P1 pbm file identical to the file
 * provided except all black edge pixels are changed to white pixels.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>
#include <bit2.h>
#include <seq.h>

struct Position {
        int col, row;
};

// Function prototypes
Bit2_T pbmread (FILE *inputfp);
void pbmwrite(FILE *outputfp, Bit2_T bitmap);
void unblack_edges(Bit2_T bitmap);
void unblack_recurse(Bit2_T bitmap, int col, int row);
int is_in_bounds(Bit2_T bitmap, int col, int row);

int main(int argc, char *argv[])
{
        Bit2_T bitmap;

        if (argc == 2) {
                char *filename = argv[1];
                FILE *fp = fopen(filename, "rb");
                if (fp == NULL) {
                        fprintf(stderr, "Invalid file name. \n");
                        exit(EXIT_FAILURE);
                }

                bitmap = pbmread(fp);
                unblack_edges(bitmap);
                fclose(fp);
        } else if (argc == 1) {
                bitmap = pbmread(stdin);
                unblack_edges(bitmap);
        } else {
                fprintf(stderr, "Too many command line arguments\n");
                exit(EXIT_FAILURE);
        }

        pbmwrite(stdout, bitmap);
        Bit2_free(&bitmap);

        return EXIT_SUCCESS;
}

/*
 * pbmread takes and reads a stream and stores the data from the file in a 
 * Bit2_T, which it then returns.
 *
 * Parameters:
 *         inputfp: The stream to read from.
 */
Bit2_T pbmread (FILE *inputfp)
{
        Pnmrdr_T rdr = Pnmrdr_new(inputfp);
        Pnmrdr_mapdata data = Pnmrdr_data(rdr);
        Bit2_T bitmap = Bit2_new(data.width, data.height);
        
        for (unsigned r = 0; r < data.height; r++) {
                for (unsigned c = 0; c < data.width; c++) {
                        int bit = Pnmrdr_get(rdr);
                        Bit2_put(bitmap, c, r, bit);
                }
        }

        Pnmrdr_free(&rdr);
        return bitmap;
}

/*
 * pbmwrite takes a stream and a Bit2_T and writes the contents of Bit2_T to
 * the stream in P1 pbm format.
 *
 * Parameters:
 *         outputfp: The stream to write to.
 *         bitmap: The Bit2_T containing the contents to write.
 */ 
void pbmwrite(FILE *outputfp, Bit2_T bitmap)
{
        int height = Bit2_height(bitmap);
        int width = Bit2_width(bitmap);

        fprintf(outputfp, "P1\n");
        fprintf(outputfp, "%d %d\n", width, height);
	
        for (int r = 0; r < height; r++) {
                for (int c = 0; c < width; c++) {
                        fprintf(outputfp, "%d", Bit2_get(bitmap, c, r));
                }
                fprintf(outputfp, "\n");
        }
        
}

/*
 * unblack_edges takes a Bit2_T and converts all black edge pixels to white
 * edge pixels.
 *
 * Parameters:
 *         bitmap: The Bit2_T from which black edges are to be removed.
 */
void unblack_edges(Bit2_T bitmap)
{
        int height = Bit2_height(bitmap);
        int width = Bit2_width(bitmap);

        for (int c = 0; c < width; c++) {
                unblack_recurse(bitmap, c, 0);
                unblack_recurse(bitmap, c, height - 1);
        }
        for (int r = 0; r < height; r++) {
                unblack_recurse(bitmap, 0, r);
                unblack_recurse(bitmap, width - 1, r);
        }
}
/*
void unblack_recurse(Bit2_T bitmap, int col, int row)
{
        if (Bit2_get(bitmap, col, row) == 0) {
                return;
        }

        Seq_T queue = Seq_new(1);
        Seq_addhi(queue, make_struct(col, row));
        while (Seq_length(queue) != 0) {
                col = ((struct Position *)Seq_get(queue, 0))->col;
                row = ((struct Position *)Seq_get(queue, 0))->row;
                Bit2_put(bitmap, col, row, 0);
                free(Seq_remlo(queue));
                
                if (is_black_edge(bitmap, col - 1, row)) {
                        Seq_addhi(queue, make_struct(col - 1, row));           
                        Bit2_put(bitmap, col - 1, row, 0);
                }
                if (is_black_edge(bitmap, col + 1, row)) {
                        Seq_addhi(queue, make_struct(col + 1, row));  
                        Bit2_put(bitmap, col + 1, row, 0);
                }
                if (is_black_edge(bitmap, col, row - 1)) {
                        Seq_addhi(queue, make_struct(col, row - 1));  
                        Bit2_put(bitmap, col, row - 1, 0);
                }
                if (is_black_edge(bitmap, col, row + 1)) {
                        Seq_addhi(queue, make_struct(col, row + 1));  
                        Bit2_put(bitmap, col, row + 1, 0);
                }
        } 
        Seq_free(&queue);
}

void *make_struct(int col, int row)
{
        struct Position *pos = malloc(sizeof(pos));
        pos->col = col;
        pos->row = row;
        void *v_ptr = pos;
        return v_ptr;
}
*/
/*
 * unblack_recurse is a recursive helper function for unblack_edges.
 *
 * Parameters:
 *         col: The column number
 *         row: The row number
 */
void unblack_recurse(Bit2_T bitmap, int col, int row)
{
        if (is_in_bounds(bitmap, col, row) && Bit2_get(bitmap, col, row)) {
                Bit2_put(bitmap, col, row, 0);
                unblack_recurse(bitmap, col - 1, row);
                unblack_recurse(bitmap, col + 1, row);
                unblack_recurse(bitmap, col, row - 1);
                unblack_recurse(bitmap, col, row + 1);
        }
}

/*
 * is_in_bounds takes a Bit2_T a column number, and a row number, and checks
 * whether the given column number and row number are in bounds given the 
 * Bit2_T. If it is it returns 1, otherwise it returns 0.
 *
 * Parameters:
 *         bitmap: The Bit2_T to compare check the column and row number with.
 *         col: The column number.
 *         row: The row number.
 */
int is_in_bounds(Bit2_T bitmap, int col, int row)
{
        int height = Bit2_height(bitmap);
        int width = Bit2_width(bitmap);

        if (col < 0 || col >= width || row < 0 || row >= height) {
                return 0;
        } else {
                return 1;
        }
}
