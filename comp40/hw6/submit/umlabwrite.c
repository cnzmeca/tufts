#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "fmt.h"
#include "seq.h"

extern void Um_write_sequence(FILE *output, Seq_T instructions);

extern void test_halt(Seq_T instructions);
extern void test_io(Seq_T instructions);
extern void test_lv(Seq_T instructions);
extern void test_add(Seq_T instructions);
extern void test_addmod(Seq_T instructions);
extern void test_mult(Seq_T instructions);
extern void test_multmod(Seq_T instructions);
extern void test_div(Seq_T instructions);
extern void test_nand(Seq_T instructions);
extern void test_cmovf(Seq_T instructions);
extern void test_cmovt(Seq_T instructions);
extern void test_sload(Seq_T instructions);
extern void test_sstore(Seq_T instructions);
extern void test_map(Seq_T instructions);
extern void test_unmap(Seq_T instructions);
extern void test_lp(Seq_T instructions);
extern void test_time(Seq_T instructions);

/* The array `tests` contains all unit tests for the lab. */

static struct test_info {
        const char *name;
        const char *test_input;          /* NULL means no input needed */
        const char *expected_output;
        /* writes instructions into sequence */
        void (*emit_test)(Seq_T stream);
} tests[] = {
        { "test_halt",         NULL, "", test_halt },
        { "test_io",         "X", "X", test_io },
        { "test_lv",         NULL, "X", test_lv },
        { "test_add",         NULL, "X", test_add },
        { "test_addmod",         NULL, "X", test_add },
        { "test_mult",         NULL, "X", test_mult },
        { "test_multmod",         NULL, "X", test_mult },
        { "test_div",         NULL, "X", test_div },
        { "test_nand",         NULL, "X", test_nand },
        { "test_cmovf",         NULL, "X", test_cmovf },
        { "test_cmovt",         NULL, "X", test_cmovt},
        { "test_sload",         NULL, "p", test_sload },
        { "test_sstore",         NULL, "X", test_sstore },
        { "test_map",         NULL, "X", test_map },
        { "test_unmap",         NULL, "", test_unmap },
        { "test_lp",         "X", "X", test_lp},
        { "test_time",         NULL, "", test_time},
};
  
#define NTESTS (sizeof(tests)/sizeof(tests[0]))

/*
 * open file 'path' for writing, then free the pathname;
 * if anything fails, checked runtime error
 */
static FILE *open_and_free_pathname(char *path);

/*
 * if contents is NULL or empty, remove the given 'path', 
 * otherwise write 'contents' into 'path'.  Either way, free 'path'.
 */
static void write_or_remove_file(char *path, const char *contents);

static void write_test_files(struct test_info *test);


int main (int argc, char *argv[])
{
        bool failed = false;
        if (argc == 1)
                for (unsigned i = 0; i < NTESTS; i++) {
                        printf("***** Writing test '%s'.\n", tests[i].name);
                        write_test_files(&tests[i]);
                }
        else
                for (int j = 1; j < argc; j++) {
                        bool tested = false;
                        for (unsigned i = 0; i < NTESTS; i++)
                                if (!strcmp(tests[i].name, argv[j])) {
                                        tested = true;
                                        write_test_files(&tests[i]);
                                }
                        if (!tested) {
                                failed = true;
                                fprintf(stderr,
                                        "***** No test named %s *****\n",
                                        argv[j]);
                        }
                }
        return failed; /* failed nonzero == exit nonzero == failure */
}


static void write_test_files(struct test_info *test)
{
        FILE *binary = open_and_free_pathname(Fmt_string("%s.um", test->name));
        Seq_T instructions = Seq_new(0);
        test->emit_test(instructions);
        Um_write_sequence(binary, instructions);
        Seq_free(&instructions);
        fclose(binary);

        write_or_remove_file(Fmt_string("%s.0", test->name),
                             test->test_input);
        write_or_remove_file(Fmt_string("%s.1", test->name),
                             test->expected_output);
}


static void write_or_remove_file(char *path, const char *contents)
{
        if (contents == NULL || *contents == '\0') {
                remove(path);
        } else {
                FILE *input = fopen(path, "wb");
                assert(input != NULL);

                fputs(contents, input);
                fclose(input);
        }
        free(path);
}


static FILE *open_and_free_pathname(char *path)
{
        FILE *fp = fopen(path, "wb");
        assert(fp != NULL);

        free(path);
        return fp;
}

extern void Um_write_sequence(FILE *output, Seq_T instructions)
{
	for (int i = 0; i < Seq_length(instructions); ++i)
	{
		uint32_t word = (uint32_t)(uintptr_t)Seq_get(instructions, i);
		for (int j = 3; j >= 0; --j) {
			uint32_t mask = ~(~0 << 8) << (j * 8);
			fputc((mask & word) >> (j * 8), output);	
		}
	}
}
