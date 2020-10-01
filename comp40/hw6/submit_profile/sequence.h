/*
* Christian Zinck and Phong Hoang
* Assignment 7: Profiling
* 4/23/18
*
* Interface for the sequence module
*/

#include <inttypes.h>

#ifndef SEQ_H_
#define SEQ_H_

typedef struct Seq *Seq;

Seq Seq_new(uint32_t size);
void Seq_free(Seq *seq);
uint32_t Seq_length(Seq seq);
uint32_t *Seq_get(Seq seq, uint32_t i);
void Seq_put(Seq seq, uint32_t i, uint32_t *x);
uint32_t *Seq_remhi(Seq seq);
void Seq_addhi(Seq seq, uint32_t *x);
#endif
