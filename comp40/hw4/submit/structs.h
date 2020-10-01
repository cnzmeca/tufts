/*
 * ppm_ypp.h
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Defines the 2 structs used throughout the project.
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct YPP {
        float y, pb, pr;
} *YPP;

typedef struct PPabcd {
        int pb, pr, a, b, c, d;
} *PPabcd;

#endif
