/*
 * ypp_ppabcd.c
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Contains functions for converting between ypp and ppabcd formats.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "arith40.h"

#include "ypp_ppabcd.h"
#include "structs.h"

/* Max and min value for b, c, and d */
#define R 31.0

/* Array of factors for scaling a, b, c, and d */
double f[4] = {63.0, R / .3, R / .3, R / .3};

PPabcd ypp_to_ppabcd(YPP* block)
{
        PPabcd ret = malloc(sizeof(*ret));
        
        float pb_sum = 0, pr_sum = 0;
        for (int i = 0; i < 4; ++i) {
                pb_sum += (block[i])->pb;
                pr_sum += (block[i])->pr;
        }

        ret->pb = Arith40_index_of_chroma(pb_sum / 4.0);
        ret->pr = Arith40_index_of_chroma(pr_sum / 4.0);
        
        float y1 = block[0]->y;
        float y2 = block[1]->y;
        float y3 = block[2]->y;
        float y4 = block[3]->y; 

        /* fmax and fmin are used to guarantee values are in correct range */
        ret->a = fmax(fmin((f[0] * (y4 + y3 + y2 + y1) / 4.0), f[0]), 0);
        ret->b = fmax(fmin((f[1] * (y4 + y3 - y2 - y1) / 4.0), R), -R); 
        ret->c = fmax(fmin((f[2] * (y4 - y3 + y2 - y1) / 4.0), R), -R); 
        ret->d = fmax(fmin((f[3] * (y4 - y3 - y2 + y1) / 4.0), R), -R); 

        return ret;
}

YPP* ppabcd_to_ypp(PPabcd data)
{
        YPP *ret = malloc(4 * sizeof(**ret));
        
        for (int i = 0; i < 4; ++i) {
                ret[i] = malloc(sizeof(**ret));
        }

        float a = data->a / ((float)f[0]);
        float b = data->b / ((float)f[1]);
        float c = data->c / ((float)f[2]);
        float d = data->d / ((float)f[3]);

        /* fmax and fmin are used to guarantee values are in correct range */
        (ret[0])->y = fmax(fmin((a - b - c + d), 1), 0);
        (ret[1])->y = fmax(fmin((a - b + c - d), 1), 0);
        (ret[2])->y = fmax(fmin((a + b - c - d), 1), 0);
        (ret[3])->y = fmax(fmin((a + b + c + d), 1), 0);

        for (int i = 0; i < 4; ++i) {   
                (ret[i])->pb = Arith40_chroma_of_index(data->pb);
                (ret[i])->pr = Arith40_chroma_of_index(data->pr);
        }

        return ret;
}


