#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "bitpack.h"

int main(void)
{
	uint64_t word = 0;
	unsigned lsb = 0;
	unsigned width = 4;
	for (int64_t val = -8 ; val <= 8; val++) {
		fprintf(stderr, "%ld\n", Bitpack_gets(Bitpack_news(word, width, lsb, val), width, lsb));
}
}
