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

void Seq_free(Seq *seq)
{
        free((*seq)->array);
        free(*seq);
	seq = NULL;
}

uint32_t Seq_length(Seq seq)
{
        return seq->size;
}

uint32_t *Seq_get(Seq seq, uint32_t i)
{
	assert(i < seq->size);
        return *(seq->array + i);
}

uint32_t *Seq_put(Seq seq, uint32_t i, uint32_t *x)
{
	assert(i < seq->size);
        uint32_t *temp = *(seq->array + i);
        *(seq->array + i) = x;
        return temp;
}

uint32_t *Seq_remhi(Seq seq)
{
        --(seq->size);
        return *(seq->array + seq->size);
}

uint32_t *Seq_addhi(Seq seq, uint32_t *x)
{
	fprintf(stderr, "hi");
        uint32_t len = seq->size;
        uint32_t max = seq->capacity;
        if (len == max) {
        	Seq ret = Seq_new((2 * max) + 2);
		ret->size = len;
		memcpy((void *) (ret->array), (void *) (seq->array), len * sizeof(uint32_t *));
		Seq_free(&seq);
		seq = ret;
	}

        ++(seq->size);
         uint32_t *temp = *(seq->array + len);
        *(seq->array + len) = x;
        return temp;
}

