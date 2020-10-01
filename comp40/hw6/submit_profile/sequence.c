/*
* Christian Zinck and Phong Hoang
* Assignment 7: Profiling
* 4/23/18
*
* Implementation for the sequence module.
*/


#include "sequence.h"

#include "assert.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

struct Seq {
        uint32_t size;
        uint32_t capacity;
        uint32_t **array;
};

/* Seq_new
 * Parameters: uint32_t size
 * Return: Seq
 *
 * Creates a new sequence of size size and returns it.
 */
Seq Seq_new(uint32_t size)
{
        Seq ret = malloc(sizeof(*ret));
        assert(ret);
        ret->size = 0;
        ret->capacity = size;
        ret->array = malloc(size * sizeof(uint32_t*));
        assert(ret->array);
        return ret;
}

/* Seq_free
 * Parameters: Seq *seq
 * Return: void
 *
 * Frees all memory associated with seq.
 */
void Seq_free(Seq *seq)
{
        free((*seq)->array);
        free(*seq);
        seq = NULL;
}

/* Seq_length
 * Parameters: Seq seq
 * Return: Seq
 *
 * Returns length of seq.
 */
uint32_t Seq_length(Seq seq)
{
        return seq->size;
}

/* Seq_get
 * Parameters: Seq seq, uint32_t i
 * Return: uint32_t*
 *
 * Gets the value at index i of seq and returns it.
 */
uint32_t *Seq_get(Seq seq, uint32_t i)
{
        return *(seq->array + i);
}

/* Seq_put
 * Parameters: Seq seq, uint32_t i, uint32_t *x
 * Return: void
 *
 * Puts x into index i of seq.
 */
void Seq_put(Seq seq, uint32_t i, uint32_t *x)
{
        *(seq->array + i) = x;
}

/* Seq_remhi
 * Parameters: Seq
 * Return: uint32_t*
 *
 * Returns and removes last element in seq.
 */
uint32_t *Seq_remhi(Seq seq)
{
        --(seq->size);
        return *(seq->array + seq->size);
}

/* Seq_addhi
 * Parameters: Seq seq, uint32_t *x
 * Return: void
 *
 * Adds x to end of seq and expands if necessary.
 */
void Seq_addhi(Seq seq, uint32_t *x)
{
        uint32_t len = seq->size;
        uint32_t max = seq->capacity;
        
        if (len == max) {
                seq->array = realloc(seq->array, 2 * max * sizeof(uint32_t *)); 
                seq->capacity = 2 * max;
        }

        ++(seq->size);
        *(seq->array + len) = x;
}

