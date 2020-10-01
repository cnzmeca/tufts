/*
* Christian Zinck and Phong Hoang
* Assignment 6: UM Design Doc
* 4/5/18
*
* Interface for the segment module
*/

#include "sequence.h"

#include <inttypes.h>

#ifndef SEGMENT_H_
#define SEGMENT_H_
#define Segment uint32_t *

Segment Segment_new(uint32_t size);
void Segment_free(Segment *seg);
void Segment_load(Seq mem, uint32_t *a, uint32_t *b, uint32_t *c);
void Segment_store(Seq mem, uint32_t *a, uint32_t *b, uint32_t *c);
void Segment_map(Seq mem, Seq unused_ids, uint32_t *b, uint32_t *c);
void Segment_unmap(Seq mem, Seq unused_ids, uint32_t *c);
uint32_t Segment_move(Seq mem, Seq unused_ids, uint32_t *b, uint32_t *c);
#endif
