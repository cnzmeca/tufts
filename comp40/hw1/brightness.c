/*
 * brightness.c
 * by Christian Zinck and Josh Mitchell. 2/1/18
 * HW 1: FilesNPix
 *
 * A program that prints the average brightness of a grayscale image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>

#define MAXFILELENGTH 20

FILE *openf(char *filename);
float calcAvg(FILE *fp);

int main(int argc, char *argv[])
{
        float avg;
        if (argc == 2) {
                char *filename = argv[1];
                FILE *fp = openf(filename);
                avg = calcAvg(fp);
                fclose(fp);
        } else if (argc == 1) {
                avg = calcAvg(stdin);
        } else {
                fprintf(stderr, "Too many command line arguments.\n");
                exit(EXIT_FAILURE);
        }
        printf("%1.3f\n", avg);
        return EXIT_SUCCESS;
}

/*
 * openF takes a c string file name, opens the file in read binary mode, and
 * returns the FILE. If the file is unable to be opened, an error is printed.
 *
 * Parameters:
 *         filename - the name of the file to be opened.
 */
FILE *openf(char *filename)
{
        FILE *fp = fopen(filename, "rb");
        if (fp == 0) {
                fprintf(stderr, "Invalid file name.\n");
                exit(EXIT_FAILURE);
        }

        return fp;
}

/*
 * calcAvg takes a FILE pointer and calculates and returns the average
 * brightness in the image using PNMRDR.
 *
 * Parameters:
 *         fp - a pointer to an open file to be analyzed.
 */
float calcAvg(FILE *fp)
{
        Pnmrdr_T rdr = Pnmrdr_new(fp);
        Pnmrdr_mapdata data = Pnmrdr_data(rdr);
        unsigned numPixs = data.height*data.width;
        for (unsigned i = 0; i < numPixs; i++) {
                int num = Pnmrdr_get(rdr);
                printf("%d ", num);
        }

        Pnmrdr_free(&rdr);
        return 1;
}
