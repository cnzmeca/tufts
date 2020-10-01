/*
 * ypp_ppabcd.h
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Interface for ypp_ppabcd.c
 */

#ifndef YPP_PPABCD_H_
#define YPP_PPABCD_H_

#include "structs.h"

extern PPabcd ypp_to_ppabcd(YPP block[]);
extern YPP* ppabcd_to_ypp(PPabcd data);

#endif
