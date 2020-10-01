/*
* Christian Zinck and Phong Hoang
* Assignment 6: UM
* 4/12/18
*
* Implementation for the operations module
*/

#include "operations.h"

#include <assert.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 4294967296

/*
 * cond_move
 * Parameters: uint32_t *a, uint32_t *b, uint32_t *c
 * Return: void
 *
 * If the content of C is nonzero, then the content of B replaces the content
 * of A.
 */
void cond_move(uint32_t *a, uint32_t *b, uint32_t *c)
{
        if (*c != 0) {
                *a = *b;
        }
}

/*
 * add
 * Parameters: uint32_t *a, uint32_t *b, uint32_t *c
 * Return: void
 *
 * The content of B is added to the content of C and the result is stored in A.
 */
void add(uint32_t *a, uint32_t *b, uint32_t *c)
{
        *a = (*b + *c) % MAX;
}

/*
 * multiply
 * Parameters: uint32_t *a, uint32_t *b, uint32_t *c
 * Return: void
 *
 * The content of B is multiplied with the content of C and the result is stored
 * in A.
 */
void multiply(uint32_t *a, uint32_t *b, uint32_t *c)
{
        *a = (*b * *c) % MAX;
}

/*
 * divide
 * Parameters: uint32_t *a, uint32_t *b, uint32_t *c
 * Return: void
 *
 * The content of C is divided from the content of B and the result is stored in
 * A.
 */
void divide(uint32_t *a, uint32_t *b, uint32_t *c)
{
        *a = *b / *c;
}

/*
 * nand
 * Parameters: uint32_t *a, uint32_t *b, uint32_t *c
 * Return: void
 *
 * The content of B is bitwise nanded with the content of C and the result is
 * stored in A.
 */
void nand(uint32_t *a, uint32_t *b, uint32_t *c)
{
        *a = ~(*b & *c);
}

/*
 * halt
 * Parameters: void
 * Return: void
 *
 * The program exits with exit success.
 */
void halt(void)
{
        exit(EXIT_SUCCESS);
}

/*
 * output
 * Parameters: uint32_t *c
 * Return: void
 *
 * Prints a character to standard out provided that C contains a number between
 * 0 and 255. CRE otherwise.
 */
void output(uint32_t *c)
{
        assert(*c <= 255);
        fprintf(stdout, "%c", (char)(*c));
}

/*
 * input
 * Parameters: uint32_t *c
 * Return: void
 *
 * Reads a character from standard in and stores it in C provided it is a number
 * between 0 and 255. CRE otherwise.
 */
void input(uint32_t *c)
{
        int temp = fgetc(stdin);
        assert(temp <= 255);
        
        // Sets c to all ones if EOF    
        if (temp == (EOF)) {
                *c = ~0;
        } else {
                *c = (uint32_t)temp;
        }
}

/*
 * load_val
 * Parameters: uint32_t *a, uint32_t val
 * Return: void
 *
 * Loads val into register A.
 */
void load_val(uint32_t *a, uint32_t val)
{
        *a = val;
}
