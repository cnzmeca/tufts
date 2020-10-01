/*
 * ppm_ypp.h
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Interface for ppm_ypp.c
 */

#ifndef PPM_YPP_H_
#define PPM_YPP_H_

#include "pnm.h"

#include "structs.h"

extern YPP ppm_to_ypp(Pnm_rgb pixel, unsigned denom);
extern Pnm_rgb ypp_to_ppm(YPP pixel, unsigned denom);

#endif
