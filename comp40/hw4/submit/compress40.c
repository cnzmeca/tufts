/*
 * compress40.c
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Contains primary functions for compression and decompression.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "assert.h"
#include "pnm.h"
#include "a2methods.h"
#include "a2plain.h"
#include "arith40.h"

#include "compress40.h"
#include "ppm_ypp.h"
#include "ypp_ppabcd.h"
#include "ppabcd_codeword.h"
#include "bitpack.h"

const unsigned DENOM = 255;
const unsigned BYTE = 8;

/* Mapping function that compresses each 2x2 block of pixels */
void comp40(int c, int r, A2Methods_UArray2 array, void *elem, void *cl)
{
        (void) elem;
        Pnm_ppm image = *((Pnm_ppm *)cl);
        
        /* Only runs compression once per 2x2 block */
        if ((c % 2 != 0) && (r % 2 != 0)) {
                YPP *block = malloc(4 * sizeof(*block));
                for (int i = 0; i < 4; ++i) {
                        Pnm_rgb ppm = image->methods->at(array,
                        /* Math to access each pixel via loop */
                        c - ((i + 1) % 2), r - 1 + (i / 2));
                        block[i] = ppm_to_ypp(ppm, image->denominator);
                }
        
                PPabcd data = ypp_to_ppabcd(block);
                for (int i = 0; i < 4; ++i){
                        free(block[i]);
                }
                free(block);
        
                uint64_t word = encode_word(data);
                free(data);             
                        
                for (int i = 3; i >= 0; --i) {
                        putchar(Bitpack_getu(word, BYTE, BYTE * i));
                }
        }

}


/* Mapping function that decompresses each 2x2 block of pixels */
void decomp40(int c, int r, A2Methods_UArray2 array, void *elem, void *cl)
{       
        (void) elem;
        FILE *fp = ((FILE *)cl);

        A2Methods_T methods = uarray2_methods_plain;
        assert(methods);

        /* Only runs decompression once per 2x2 block */
        if (c % 2 != 0 && r % 2 != 0) {
                uint64_t word;
                for (int i = 3; i >= 0; --i) {
                        uint64_t input = getc(fp);
                        word = Bitpack_newu(word, BYTE, BYTE * i, input);
                }
                
                PPabcd data = decode_word(word);

                YPP *block = ppabcd_to_ypp(data);
                free(data);
        
                for (int i = 0; i < 4; ++i) {
                        Pnm_rgb ppm = ypp_to_ppm(block[i], DENOM);
                        free(block[i]);
                        *((Pnm_rgb)methods->at(array,
                        /* Math to access each pixel via loop */
                        c - ((i + 1) % 2), r - 1 + (i / 2))) = *ppm;
                        free(ppm);
                }
                free(block);
        }
}

/* Compresses an image provided by "fp" */
void compress40  (FILE *fp)
{
        assert(fp);

        A2Methods_T methods = uarray2_methods_plain;
        assert(methods);
        
        Pnm_ppm image = Pnm_ppmread(fp, methods);
        assert(image);

        image->width = image->width - ((image->width)%2);
        image->height = image->height - ((image->height)%2);
       
        unsigned w = image->width;
        unsigned h = image->height;
        printf("COMP40 Compressed image format 2\n%u %u\n", w, h);

        methods->map_row_major(image->pixels, comp40, ((void *)&image)); 
        Pnm_ppmfree(&image);
}


/* Decompresses an image provided by "fp" */
void decompress40(FILE *fp)
{
        assert(fp);

        A2Methods_T methods = uarray2_methods_plain;
        assert(methods);
        
        unsigned w, h;
        int r = fscanf(fp, "COMP40 Compressed image format 2\n%u %u", &w, &h);
        assert(r == 2);
        int c = getc(fp);
        assert(c == '\n');

        A2Methods_UArray2 array = methods->new(w, h, sizeof(struct Pnm_rgb));
        assert(array);

        struct Pnm_ppm image = {
                .width = w,
                .height = h,
                .denominator = DENOM,
                .pixels = array,
                .methods = methods
        };

        methods->map_row_major(array, decomp40, fp);

        Pnm_ppmwrite(stdout, &image);
        methods->free(&array);
}
