/*
* Christian Zinck and Phong Hoang
* Assignment 6: UM
* 4/12/18
*
* Main file for the UM project
*/

#include "segment.h"
#include "sequence.h"

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>

#define MAX 4294967296

typedef struct UM {
        Seq mem;
        Seq unused_ids;
        uint32_t *registers;
        uint32_t prog_count;
} *UM;

/*
 * new_UM
 * Paremeters: void
 * Return: UM
 *
 * Returns a new UM.
 */
UM new_UM(void)
{
        UM ret = malloc(sizeof(*ret));
        ret->mem = Seq_new(10);
        assert(ret->mem);
        ret->unused_ids = Seq_new(10);
        assert(ret->unused_ids);
        ret->registers = calloc(8, sizeof(uint32_t));
        assert(ret->registers);
        ret->prog_count = 0;
        return ret;
}

/*
 * free_UM
 * Paremeters: UM *um
 * Return: void
 *
 * Frees all memory associated with um.
 */
void free_UM(UM *um)
{
        Seq mem = (*um)->mem;
        Seq unused_ids = (*um)->unused_ids;

	int len = Seq_length(mem);
        for (int i = 0; i < len; ++i) {
                Segment temp = Seq_get(mem, i);
                if (temp != NULL) {
                        Segment_free(&temp);
                }
        }
        Seq_free(&mem);
        Seq_free(&unused_ids);
        free((*um)->registers);
        free(*um);
}

/*
 * load_UM_Data
 * Paremeters: Um um, char *fname
 * Return: void
 *
 * Loads words stored in file with name fname and puts them in segment 0 of um.
 */
void load_UM_Data(UM um, char *fname)
{
        // Opens file to get size in words
        FILE *fp = fopen(fname, "rb");
        assert(fp);
        int c;
        uint32_t size = 0, zero = 0;
        while ((c = fgetc(fp)) != EOF) {
                ++size;
        }
        size = size / 4;
        fclose(fp);

        // Opens file and stores all words in segment 0
        fp = fopen(fname, "rb");
        assert(fp);
        Segment_map(um->mem, um->unused_ids, &zero, &size);
        for (uint32_t i = 0; i < size; ++i) {
                // Assembles word from separate bytes
                uint32_t word = 0;
                for (int j = 3; j >= 0; --j) {
                        c = fgetc(fp);
                        word += (c << (j * 8));
                }
                Segment_store(um->mem, &zero, &i, &word);
        }
        fclose(fp);     
}

int main(int argc, char *argv[])

{
        if (argc != 2) {
                fprintf(stderr, "Invalid call. Use './um [filename]'\n");
                exit(EXIT_FAILURE);
        }
        UM um = new_UM();

        load_UM_Data(um, argv[1]);

	uint32_t word = 0;
        uint32_t zero = 0;
	uint32_t op_lsb = 28;
        uint32_t a_lsb = 6;
        uint32_t b_lsb = 3;
        uint32_t val_len = 25;
	uint32_t reg_size = 3;
        uint32_t lv_op = 13;

	uint32_t op_mask = ~zero << op_lsb;
	uint32_t a_mask = ~(~zero << reg_size) << a_lsb;
	uint32_t a_lv_mask = ~(~zero << reg_size) << val_len;
	uint32_t b_mask = ~(~zero << reg_size) << b_lsb;
	uint32_t c_mask = ~(~zero << reg_size);
	uint32_t val_mask = ~(~zero << val_len);
	
        uint32_t op, val, rega, regb, regc;
	uint32_t *a, *b, *c;
        uint32_t *regs = um->registers;
	uint32_t *pc = &(um->prog_count);

        while (1) {
		Segment_load(um->mem, &word, &zero, pc); 
                ++(*pc);

		for (int i = 0; i < 8; ++i) {
               		fprintf(stderr, "%d:%u ", i, *(regs + i));
		}
		fprintf(stderr, "%x\n", word);
		
                op = (word & op_mask) >> op_lsb;
        
                // Special case for load_val
                if (op == lv_op) {
                        rega = (word & a_lv_mask) >> val_len;
                        val = word & val_mask;
                // Other cases
                } else {
                        rega = (word & a_mask) >> a_lsb;
                        regb = (word & b_mask) >> b_lsb;
                        regc = word & c_mask;
                }
        	
		a = regs + rega;
		b = regs + regb;
		c = regs + regc;
	
		if (op == 13) {
			*a = val;
		} else if (op == 1) {
                        Segment_load(um->mem, a, b, c);
		} else if (op == 2) {
                        Segment_store(um->mem, a, b, c);
		} else if (op == 6) {
                       	*a = ~(*b & *c);
		} else if (op == 3) {
                        *a = (*b + *c) % MAX;
		} else if (op == 12) {
			um->prog_count = Segment_move(um->mem, um->unused_ids,
						      b, c);
		} else if (op == 0) {
			if (*c != 0) {
                        	*a = *b;
                        }
		} else if (op == 8) {
                	Segment_map(um->mem, um->unused_ids, b, c);
		} else if (op == 9) {
                        Segment_unmap(um->mem, um->unused_ids, c);
		} else if (op == 5) {
                       	*a = *b / *c;
		} else if (op == 4) {
                        *a = (*b * *c) % MAX;
		} else if (op == 10) {
                      	fprintf(stdout, "%c", (char)(*c));
		} else if (op == 11) {
			*c = fgetc(stdin);
                        // Sets c to all ones if EOF    
                        if (*c == (unsigned)(EOF)) {
                        	*c = ~0;
                        }
		} else if (op == 7) {
			free_UM(&um);
                        exit(EXIT_SUCCESS);
		}
        }       
        exit(EXIT_SUCCESS);
}
