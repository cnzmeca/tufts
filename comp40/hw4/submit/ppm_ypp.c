/*
 * ppm_ypp.c
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Contains functions for converting between ppm and ypp formats.
 */

#include <math.h>
#include <stdlib.h>

#include "ppm_ypp.h"
#include "structs.h"

/* Converts an rgb pixel to a component video pixel */
YPP ppm_to_ypp(Pnm_rgb pixel, unsigned denom)
{
        YPP ret = malloc(sizeof(*ret));
        
        float r = ((float)pixel->red) / ((float)denom);
        float g = ((float)pixel->green) / ((float)denom);
        float b = ((float)pixel->blue) / ((float)denom);

        /* fmax and fmin are used to guarantee values are in correct range */
        ret->y = fmax(fmin((.299 * r + .587 * g + .114 * b), 1), 0);
        ret->pb = fmax(fmin((-.168736 * r - .331264 * g + .5 * b), .5), -.5);
        ret->pr = fmax(fmin((.5 * r - .418688 * g - .081312 * b), .5), -.5);
        
        return ret;
}


/* Converts a component video pixel to an rgb pixel */
Pnm_rgb ypp_to_ppm(YPP pixel, unsigned denom)
{
        Pnm_rgb ret = malloc(sizeof(*ret));
        
        float y = ((float)denom) * pixel->y;
        float pb = ((float)denom) * pixel->pb;
        float pr = ((float)denom) * pixel->pr;

        /* fmax and fmin are used to guarantee values are in correct range */
        ret->red = fmax(fmin((y + 1.402 * pr), denom), 0);
        ret->green = fmax(fmin((y - .344136 * pb - .714136 * pr), denom), 0);
        ret->blue = fmax(fmin((y + 1.772 * pb), denom), 0);

        return ret;
        
}
