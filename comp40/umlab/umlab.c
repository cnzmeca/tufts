/*
 * umlab.c
 * 
 * The functions defined in this lab should be linked against umlabwrite.c
 * to produce a unit test writing program. Any additional functions and unit
 * tests written for the lab go here.
 */

#include <stdint.h>
#include <stdio.h>

#include <assert.h>
#include <seq.h>


typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;


/* Functions that return the two instruction types */

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
        Um_instruction ret = op << 28;
        ret += ((ra << 6) + (rb << 3) + rc);
        return ret;
}

Um_instruction loadval(unsigned ra, unsigned val)
{
        Um_instruction ret = LV << 28;
        ret += ((ra << 25) + val);
        return ret;
}

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;


/* Functions for working with streams */

static inline void emit(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

extern void Um_write_sequence(FILE *output, Seq_T stream);


/* Unit tests for the UM, which are explained in README*/

void test_halt(Seq_T stream)
{
	emit(stream, three_register(HALT, 0, 0, 0));
}

void test_io(Seq_T stream)
{
	emit(stream, three_register(IN, 0, 0, 0));
	emit(stream, three_register(OUT, 0, 0, 0));
	emit(stream, three_register(HALT, 0, 0, 0));
}

void test_lv(Seq_T stream)
{
	emit(stream, loadval(0, 88));
	emit(stream, three_register(OUT, 0, 0, 0));
	emit(stream, three_register(HALT, 0, 0, 0));
}

void test_add(Seq_T stream)
{	
	emit(stream, loadval(1, 80));
	emit(stream, loadval(2, 8));
	emit(stream, three_register(ADD, 0, 1, 2));
	emit(stream, three_register(OUT, 0, 0, 0));
	emit(stream, three_register(HALT, 0, 0, 0));
	
}

void test_mult(Seq_T stream)
{
	emit(stream, loadval(1, 8));
        emit(stream, loadval(2, 11));
        emit(stream, three_register(MUL, 0, 1, 2));
        emit(stream, three_register(OUT, 0, 0, 0));
        emit(stream, three_register(HALT, 0, 0, 0));
}

void test_div(Seq_T stream)
{
	emit(stream, loadval(1, 176));
        emit(stream, loadval(2, 2));
        emit(stream, three_register(DIV, 0, 1, 2));
        emit(stream, three_register(OUT, 0, 0, 0));
        emit(stream, three_register(HALT, 0, 0, 0));
}

void test_nand(Seq_T stream)
{
	emit(stream, loadval(1, ~0));
        emit(stream, loadval(2, ~0));
        emit(stream, loadval(3, 48));
        emit(stream, loadval(4, 2));
        emit(stream, three_register(NAND, 0, 1, 2));
        emit(stream, three_register(DIV, 0, 0, 1));
        emit(stream, three_register(ADD, 0, 0, 3));
        emit(stream, three_register(DIV, 0, 0, 4));	
        emit(stream, three_register(OUT, 0, 0, 0));	
        emit(stream, three_register(HALT, 0, 0, 0));
}

void test_cmovf(Seq_T stream)
{
	emit(stream, loadval(0, 88));
	emit(stream, loadval(1, 0));
	emit(stream, loadval(2, 0));
        emit(stream, three_register(CMOV, 0, 1, 2));
        emit(stream, three_register(OUT, 0, 0, 0));
        emit(stream, three_register(HALT, 0, 0, 0));
}

void test_cmovt(Seq_T stream)
{
	emit(stream, loadval(0, 0));
	emit(stream, loadval(1, 88));
	emit(stream, loadval(2, 1));
        emit(stream, three_register(CMOV, 0, 1, 2));
        emit(stream, three_register(OUT, 0, 0, 0));
        emit(stream, three_register(HALT, 0, 0, 0));
}

void test_sload(Seq_T stream)
{
	emit(stream, loadval(1, 0));
        emit(stream, loadval(2, 6));
        emit(stream, loadval(3, (1 << 24)));
	emit(stream, three_register(SLOAD, 0, 1, 2));
        emit(stream, three_register(DIV, 0, 0, 3));	
        emit(stream, three_register(OUT, 0, 0, 0));
        emit(stream, three_register(HALT, 0, 0, 0));
}

void test_sstore(Seq_T stream)
{
	emit(stream, loadval(1, 0));
        emit(stream, loadval(2, 88));
	emit(stream, three_register(SSTORE, 1, 1, 2));
	emit(stream, three_register(SLOAD, 0, 1, 1));
	emit(stream, three_register(OUT, 0, 0, 0));
        emit(stream, three_register(HALT, 0, 0, 0));
}

void test_map(Seq_T stream)
{
	emit(stream, loadval(1, 0));
	emit(stream, loadval(2, 1));
	emit(stream, loadval(3, 88));
	emit(stream, three_register(ACTIVATE, 0, 4, 2));
	emit(stream, three_register(SLOAD, 0, 4, 1));	
	emit(stream, three_register(CMOV, 3, 1, 0));
	emit(stream, three_register(OUT, 0, 0, 3));
        emit(stream, three_register(HALT, 0, 0, 0));
}

void test_unmap(Seq_T stream)
{
        emit(stream, loadval(2, 1));
        emit(stream, three_register(ACTIVATE, 0, 3, 2));
        emit(stream, three_register(INACTIVATE, 0, 0, 3));
        emit(stream, three_register(ACTIVATE, 0, 3, 2));
        emit(stream, three_register(INACTIVATE, 0, 0, 3));
	emit(stream, three_register(HALT, 0, 0, 0));
	
}

void test_lp(Seq_T stream)
{
	emit(stream, loadval(1, 176));
	emit(stream, loadval(2, 160));
	emit(stream, loadval(3, 112));
	emit(stream, loadval(4, (1 << 24)));
        emit(stream, three_register(MUL, 1, 1, 4));
        emit(stream, three_register(MUL, 2, 2, 4));
        emit(stream, three_register(MUL, 3, 3, 4));

	emit(stream, loadval(0, 0));
	emit(stream, loadval(6, 2));
	emit(stream, loadval(7, 3));

        emit(stream, three_register(ACTIVATE, 0, 5, 7));
	emit(stream, three_register(SSTORE, 5, 0, 1));
	emit(stream, three_register(SSTORE, 5, 5, 2));
	emit(stream, three_register(SSTORE, 5, 6, 3));

	emit(stream, three_register(LOADP, 0, 5, 0));
	emit(stream, three_register(HALT, 0, 0, 0));
}

void test_time(Seq_T stream)
{
	emit(stream, loadval(0, 0));
	emit(stream, loadval(1, 5000000));
	emit(stream, loadval(3, 4));
        emit(stream, three_register(NAND, 4, 0, 0));
	emit(stream, loadval(5, 1));
	
	emit(stream, loadval(2, 15));
	
	emit(stream, three_register(ACTIVATE, 0, 6, 5));
	emit(stream, three_register(INACTIVATE, 0, 0, 6));
	emit(stream, three_register(ACTIVATE, 0, 6, 5));
        emit(stream, three_register(INACTIVATE, 0, 0, 6));
	emit(stream, three_register(ACTIVATE, 0, 6, 5));
        emit(stream, three_register(INACTIVATE, 0, 0, 6));


	emit(stream, three_register(ADD, 1, 1, 4));
        emit(stream, three_register(CMOV, 2, 3, 1));
        emit(stream, three_register(LOADP, 0, 0, 2));
        emit(stream, three_register(HALT, 2, 3, 1));
}

void test_addmod(Seq_T stream)
{
	
	emit(stream, loadval(1, (1 << 7)));
	emit(stream, loadval(2, (1 << 7)));
	emit(stream, loadval(3, (1 << 24)));
	emit(stream, loadval(4, 88));
	
	emit(stream, three_register(MUL, 1, 1, 3));
	emit(stream, three_register(MUL, 2, 2, 3));
	emit(stream, three_register(ADD, 0, 1, 2));
	emit(stream, three_register(ADD, 0, 0, 4));
	emit(stream, three_register(OUT, 0, 0, 0));
	emit(stream, three_register(HALT, 0, 0, 0));
}

void test_multmod(Seq_T stream)
{

        emit(stream, loadval(2, (1 << 8)));
        emit(stream, loadval(3, (1 << 24)));
        emit(stream, loadval(4, 88));

        emit(stream, three_register(MUL, 0, 2, 3));
        emit(stream, three_register(ADD, 0, 0, 4));
        emit(stream, three_register(OUT, 0, 0, 0));
        emit(stream, three_register(HALT, 0, 0, 0));
}

