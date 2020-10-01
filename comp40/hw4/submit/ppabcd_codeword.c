/*
 * ppabcd_codeword.c
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Contains functions for converting between ppabcd and codeword formats.
 */

#include <stdlib.h>
#include <stdint.h>

#include "ppabcd_codeword.h"
#include "bitpack.h"
#include "structs.h"

/* Array of sizes in bits of each data member */
int s[6] = {4, 4, 6, 6, 6, 6}; 

/* Encodes a word defined by the information in "data" */
uint64_t encode_word(PPabcd data)
{
        uint64_t word = 0;
        int lsb = 0;
        word = Bitpack_newu(word, s[0], lsb, (uint64_t)data->pr);
        word = Bitpack_newu(word, s[1], lsb += s[0], (uint64_t)data->pb);
        word = Bitpack_news(word, s[2], lsb += s[1], (int64_t)data->d);
        word = Bitpack_news(word, s[3], lsb += s[2], (int64_t)data->c);
        word = Bitpack_news(word, s[4], lsb += s[3], (int64_t)data->b);
        word = Bitpack_newu(word, s[5], lsb += s[4], (uint64_t)data->a);

        return word;
}

/* Decodes information from "word" and returns it */
PPabcd decode_word(uint64_t word)
{
        PPabcd ret = malloc(sizeof(*ret));
        
        int lsb = 0;
        ret->pr = Bitpack_getu(word, s[0], lsb);
        ret->pb = Bitpack_getu(word, s[1], lsb += s[0]);
        ret->d = Bitpack_gets(word, s[2], lsb += s[1]);
        ret->c = Bitpack_gets(word, s[3], lsb += s[2]);
        ret->b = Bitpack_gets(word, s[4], lsb += s[3]);
        ret->a = Bitpack_getu(word, s[5], lsb += s[4]);

        return ret;
}
