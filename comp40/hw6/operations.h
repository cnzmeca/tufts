/*
* Christian Zinck and Phong Hoang
* Assignment 6: UM
* 4/12/18
*
* Interface for the operations module
*/

#include <inttypes.h>

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

void cond_move(uint32_t *a, uint32_t *b, uint32_t *c);
void add(uint32_t *a, uint32_t *b, uint32_t *c);
void multiply(uint32_t *a, uint32_t *b, uint32_t *c);
void divide(uint32_t *a, uint32_t *b, uint32_t *c);
void nand(uint32_t *a, uint32_t *b, uint32_t *c);
void halt();
void output(uint32_t *c);
void input(uint32_t *c);
void load_val(uint32_t *a, uint32_t val);

#endif
