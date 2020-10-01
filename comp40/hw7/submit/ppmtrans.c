/*
 * ppmtrans.c
 * by Christian Zinck and Josh Mitchell. 2/22/18
 * HW 3: Locality
 *
 * A program that takes a ppm image file via command line arguments or stdin and
 * applies a given rotation using a given mapping order and writes the rotated
 * image to stdout. The program also supports the option to write timing data to
 * a file provided in the command line.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"
#include "cputiming.h"

#define SET_METHODS(METHODS, MAP, WHAT) do {                    \
        methods = (METHODS);                                    \
        assert(methods != NULL);                                \
        map = methods->MAP;                                     \
        if (map == NULL) {                                      \
                fprintf(stderr, "%s does not support "          \
                                WHAT "mapping\n",               \
                                argv[0]);                       \
                exit(1);                                        \
        }                                                       \
} while (0)

struct Closure {
        Pnm_ppm pixmap;
        int rotation;
};

/*
 * usage takes a c string program name and uses it to print an error message to
 * stderr.
 * 
 * Parameters:
 *         progname: The name of the program
 */
static void usage(const char *progname)
{
        fprintf(stderr, "Usage: %s [-rotate <angle>] "
                        "[-{row,col,block}-major] [filename]\n",
                        progname);
        exit(1);
}

/*
 * rotate is an apply function that takes a column number, row number, a 2d
 * array, a void pointer to the element at the position, and a void pointer for
 * extra information and rotates the image by the degree value stored in cl.
 * rray2_height(array2b->blocks)
 * Parameters:
 *         col: The column number
 *         row: The row number
 *         pixels: The image to be rotated
 *         elem: The element at position (col, row)
 *         cl: A struct containing extra information
 */
void rotate(int col, int row, A2Methods_UArray2 pixels, void *elem, void *cl)
{
        (void) pixels;

        struct Closure *c = (struct Closure *) cl;
        const struct A2Methods_T *methods = c->pixmap->methods;
        int h = c->pixmap->height;
        int w = c->pixmap->width;

        if (c->rotation == 90) {
                Pnm_rgb p = (methods->at(c->pixmap->pixels, w - row - 1, col));
                *p = *((Pnm_rgb)elem);
        } else if (c->rotation == 180) {
                Pnm_rgb p = (methods->at(c->pixmap->pixels, w - col - 1, 
                                                              h - row - 1));
                *p = *((Pnm_rgb)elem);
        } else if (c->rotation == 270) {
                Pnm_rgb p = (methods->at(c->pixmap->pixels, row, h - col - 1));
                *p = *((Pnm_rgb)elem);
        }
}

/*
 * transform takes an ppm image, a method suite, a rotation in degrees, and a
 * pointer to a timing file and applies the given rotation using the method
 * suite, writes the timing data to a file if the file provided is not null, and
 * returns a struct Closure containing the transformed image
 *
 * Parameters:
 *         pixmap: The image to be rotated
 *         methods: The method suite for image operations
 *         rotation: The number of degrees to rotate the image by
 *         timing_file: The pointer to a timing file to be written to
 */
struct Closure *transform(Pnm_ppm pixmap, A2Methods_mapfun *map, int rotation,
               FILE *timing_file)
{
        const struct A2Methods_T *methods = pixmap->methods;
        Pnm_ppm new_pixmap = malloc(sizeof(*new_pixmap));
        assert(new_pixmap);
        if (rotation == 0 || rotation == 180) {
                new_pixmap->pixels = methods->new(pixmap->width, pixmap->height,
                                     methods->size(pixmap->pixels));
                new_pixmap->width = pixmap->width;
                new_pixmap->height = pixmap->height;
        } else {
                new_pixmap->pixels = methods->new(pixmap->height, pixmap->width,
                                     methods->size(pixmap->pixels));
                new_pixmap->width = pixmap->height;
                new_pixmap->height = pixmap->width;;
        }
        new_pixmap->denominator = pixmap->denominator;
        new_pixmap->methods = pixmap->methods;
         
        struct Closure *cl = malloc(sizeof(*cl));
        assert(cl);
        cl->pixmap = new_pixmap;
        cl->rotation = rotation;
       
        if (timing_file != NULL) { 
                CPUTime_T timer = CPUTime_New();
                assert(timer);
                CPUTime_Start(timer);
                map(pixmap->pixels, rotate, (void *)cl);
                double time = CPUTime_Stop(timer);
                CPUTime_Free(&timer);
                double pixtime = time / (pixmap->width * pixmap->height);
                fprintf(timing_file, "%d %f %f\n", rotation, time, pixtime);
        } else {
                map(pixmap->pixels, rotate, (void *)cl);
        }

        return cl;
}



int main(int argc, char *argv[]) 
{
        char *time_file_name = NULL;
        char *image_name     = NULL;
        int   rotation       = 0;
        int   i;

        /* default to UArray2 methods */
        A2Methods_T methods = uarray2_methods_plain; 
        assert(methods);

        /* default to best map */
        A2Methods_mapfun *map = methods->map_default; 
        assert(map);

        for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-row-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_row_major, 
                                    "row-major");
                } else if (strcmp(argv[i], "-col-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_col_major, 
                                    "column-major");
                } else if (strcmp(argv[i], "-block-major") == 0) {
                        SET_METHODS(uarray2_methods_blocked, map_block_major,
                                    "block-major");
                } else if (strcmp(argv[i], "-rotate") == 0) {
                        if (!(i + 1 < argc)) {      /* no rotate value */
                                usage(argv[0]);
                        }
                        char *endptr;
                        rotation = strtol(argv[++i], &endptr, 10);
                        if (!(rotation == 0 || rotation == 90 ||
                            rotation == 180 || rotation == 270)) {
                                fprintf(stderr, 
                                        "Rotation must be 0, 90 180 or 270\n");
                                usage(argv[0]);
                        }
                        if (!(*endptr == '\0')) {    /* Not a number */
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-flip") == 0) {
                        usage(argv[0]);
                } else if (strcmp(argv[i], "-transpose") == 0) { 
                        usage(argv[0]);
                } else if (strcmp(argv[i], "-time") == 0) {
                        time_file_name = argv[++i];
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n", argv[0],
                                argv[i]);
                } else if (argc - i > 1) {
                        fprintf(stderr, "Too many arguments\n");
                        usage(argv[0]);
                } else {
                        break;
                }
        }

        FILE *timing_file = NULL;
        if (time_file_name != NULL) {
                timing_file = fopen(time_file_name, "a");
                assert(timing_file);
        }

        Pnm_ppm pixmap;
        
        if (i < argc) {
                image_name = argv[i];
                FILE *fp = fopen(image_name, "r");
                assert(fp);
                pixmap = Pnm_ppmread(fp, methods);
                fclose(fp);
        } else {
                 pixmap = Pnm_ppmread(stdin, methods);
        }

        assert(pixmap);

        if (rotation == 0) {
                Pnm_ppmwrite(stdout, pixmap);
        } else {
                struct Closure *cl;
                cl = transform(pixmap, map, rotation, timing_file);
                Pnm_ppmwrite(stdout, cl->pixmap);
                Pnm_ppmfree(&(cl->pixmap));
                free(cl);
        }

        Pnm_ppmfree(&pixmap); 
        
        if (time_file_name != NULL) {
                fclose(timing_file);
        }
        exit(EXIT_SUCCESS);
}
