/*
 * bitpack.c
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Module containing functions for packing codeword using bit manipulations. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "assert.h"
#include "except.h"

#include "bitpack.h"

#define SIZE 64

Except_T Bitpack_Overflow = { "Overflow packing bits" };

/* Returns true if unsigned "n" can fit in "width" bits */
bool Bitpack_fitsu(uint64_t n, unsigned width)
{
        assert(width <= SIZE);
        if (width == SIZE) {
                return true;
        } else {
                return (((~(~((uint64_t)0) << width)) & n) == n);
        }
}

/* Returns true if signed "n" can fit in "width" bits */
bool Bitpack_fitss(int64_t n, unsigned width)
{
        assert(width <= SIZE);
        uint64_t mask = ((uint64_t)1 << (width - 1));
        if (width == 0) {
                return (n == 0);
        } else if ((mask & n)  == mask) {
                return Bitpack_fitsu(~n, width - 1);
        } else {
                return Bitpack_fitsu(n, width - 1);     
        }
}

/* Returns "width" bits from unsigned "word" starting at bit "lsb" */
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
        assert(width <= SIZE);
        assert(width + lsb <= SIZE);
        if (width == SIZE) {
                return word;
        } else {
                return ((((~(~0 << width)) << lsb) & word) >> lsb);
        }
}

/* Returns "width" bits from signed "word" starting at bit "lsb" */
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb)
{
        assert(width <= SIZE);
        assert(width + lsb <= SIZE);
        uint64_t mask = ((uint64_t)1 << (width + lsb - 1));
        if (width == 0) {
                return 0;
        } else if ((word & mask) == mask) {
                return ~Bitpack_getu(~word, width - 1, lsb);    
                printf("hi");
        } else {
                return Bitpack_getu(word, width - 1, lsb);
        }
}

/* Returns new word that is "word" with "width" bits replaced by unsigned
 * "value" starting at bit "lsb"*/
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb,
                      uint64_t value)
{
        assert(width <= SIZE);
        assert(width + lsb <= SIZE);
        
        
        if (!Bitpack_fitsu(value, width)) {
                RAISE(Bitpack_Overflow);
        }

        uint64_t mask = ~((~(~(uint64_t)0 << width)) << lsb);
        return ((word & mask) | (value << lsb));
}

/* Returns new word that is "word" with "width" bits replaced by signed
 * "value" starting at bit "lsb"*/
uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb,
                      int64_t value)
{
        assert(width <= SIZE);
        assert(width + lsb <= SIZE);
        
        if (!Bitpack_fitss(value, width)) {
                RAISE(Bitpack_Overflow);
        }

        uint64_t mask = ~((~(~(uint64_t)0 << width)) << lsb);
        return ((word & mask) | (value << lsb));
}
