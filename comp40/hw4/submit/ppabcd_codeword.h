/*
 * ppabcd_codeword.h
 * Christian Zinck 3/8/18
 * Assignment 4: Arith
 *
 * Interface for ppabcd_codeword.c
 */

#ifndef PPABCD_CORDWORD_H_
#define PPABCD_CODEWORD_H_

#include "stdint.h"

#include "structs.h"

extern uint64_t encode_word(PPabcd data);
extern PPabcd decode_word(uint64_t word);

#endif
