#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "assert.h"
#include "pnm.h"
#include "a2methods.h"
#include "a2blocked.h"
#include "a2plain.h"
#include "arith40.h"

typedef struct Cl {
	Pnm_ppm p2;
	double ret;
} *Cl;

void compute(int c, int r, A2Methods_UArray2 array, void *elem, void *cl)
{
        Cl l = (Cl)cl;
        Pnm_rgb rgb = (Pnm_rgb)elem;

	
	
        int r1 = rgb->red;
        int r2 = ((Pnm_rgb)l->p2->methods->at(l->p2->pixels, c, r))->red;

        int g1 = rgb->green;
        int g2 = ((Pnm_rgb)l->p2->methods->at(l->p2->pixels, c, r))->green;

        int b1 = rgb->blue;
        int b2 = ((Pnm_rgb)l->p2->methods->at(l->p2->pixels, c, r))->blue;

        int x = pow((r1 - r2), 2) + pow((g1 - g2), 2) + pow((b1 - b2), 2);

        int w = l->p2->methods->width(array);
        int h = l->p2->methods->height(array);
        l->ret += ((double)x)/(3 * w * h);
}


int main(int argc, char*argv[])
{
	(void) argc;
	FILE *fp1, *fp2;
	if (argv[1][0] != '-') {
		fp1 = fopen(argv[1], "rb");
	} else {
		fp1 = stdin;
	}

	if (argv[2][0] != '-') {
                fp2 = fopen(argv[2], "rb");
        } else {
                fp2 = stdin;
        }

	assert(fp1 != fp2);

	A2Methods_T methods = uarray2_methods_plain;
	Pnm_ppm ppm1 = Pnm_ppmread(fp1, methods);
	Pnm_ppm ppm2 = Pnm_ppmread(fp2, methods);
	
	Cl cl = malloc(sizeof(*cl));
	cl->p2 = ppm2;
	cl->ret = 0.0;

	ppm1->height = fmin(ppm1->height, ppm2->height);
	ppm1->width = fmin(ppm1->width, ppm2->width);

	methods->map_row_major(ppm1->pixels, compute, (void *)cl);

	fprintf(stdout, "%.4f\n", sqrt(cl->ret)/ppm1->denominator);

	free(cl);
	Pnm_ppmfree(&ppm1);
	Pnm_ppmfree(&ppm2);
}
