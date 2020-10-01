/*
* Christian Zinck and Phong Hoang
* Assignment 6: UM
* 4/12/18
*
* Implementation for the segment module.
*/


#include "segment.h"
#include "sequence.h"

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>

/*
 * Segment_new
 * Parameters: uint32_t size
 * Return: Segment
 *
 * Creates a new segment with size size and returns it.
 */
Segment Segment_new(uint32_t size)
{
        Segment ret = calloc(size + 1, sizeof(uint32_t));
        assert(ret);
        ret[0] = size;
        return ret;
}

/*
 * Segment_free
 * Parameters: Segment *seg
 * Return: void
 *
 * Frees memory pointed to by seg.
 */
void Segment_free(Segment *seg)
{       
        free(*seg);
	seg = NULL;
}

/*
 * Segment_load
 * Parameters: Seq_T mem, uint32_t *a, uint32_t *b, uint32_t *c
 * Return: void
 *
 * Loads segment B, word C from mem and stores it in A.
 */
void Segment_load(Seq mem, uint32_t *a, uint32_t *b, uint32_t *c)
{
        Segment seg = Seq_get(mem, *b);
        *a = *(seg + *c + 1);
}

/*
 * Segment_store
 * Parameters: Seq_T mem, uint32_t *a, uint32_t *b, uint32_t *c
 * Return: void
 *
 * Stores the contents of C in segment A, word B in mem.
 */
void Segment_store(Seq mem, uint32_t *a, uint32_t *b, uint32_t *c)
{
        Segment seg = Seq_get(mem, *a);
        *(seg + *b + 1) = *c;
        
}

/*
 * Segment_map
 * Parameters: Seq_T mem, Seq_T unused_ids, uint32_t *b, uint32_t *c
 * Return: void
 *
 * Maps a segment of size c to segment b in mem.
 */
void Segment_map(Seq mem, Seq unused_ids, uint32_t *b, uint32_t *c)
{
        Segment seg = Segment_new(*c);
        assert(seg);

        uint32_t len = Seq_length(mem);
        // If unused_ids stack is empty, add to end of sequence
        if (Seq_length(unused_ids) == 0) {
                *b = len;
                Seq_addhi(mem, seg);
        // Otherwise pop from unused_ids stack
        } else {
                *b = *Seq_remhi(unused_ids);
		Seq_put(mem, *b, seg);
        }
}

/*
 * Segment_unmap
 * Parameters: Seq_T mem, Seq_T unused_ids, uint32_t *c
 * Return: void
 *
 * Unmaps segment c in mem and stores c in unused_ids.
 */
void Segment_unmap(Seq mem, Seq unused_ids, uint32_t *c)
{
        Segment seg = Seq_get(mem, *c);
        Segment_free(&seg);
        Seq_addhi(unused_ids, c);
        Seq_put(mem, *c, NULL);
}

/*
 * Segment_move
 * Parameters: Seq_T mem, Seq_T unused_ids, uint32_t *b, uint32_t *c
 * Return: uint32_t
 *
 * Moves segment b to segment 0 in mem and sets the program counter to c by
 * returning it.
 */
uint32_t Segment_move(Seq mem, Seq unused_ids, uint32_t *b, uint32_t *c)
{
        if (*b != 0) {
                uint32_t zero = 0;
                Segment src = Seq_get(mem, *b);
                Segment dest = Seq_get(mem, zero);
                
                uint32_t size = *src;
                Segment_unmap(mem, unused_ids, &zero);  
                Segment_map(mem, unused_ids, &zero, &size); 
                memcpy((void *)dest, (void *)src, size * sizeof(*dest));
        }
        return *c;      
}
