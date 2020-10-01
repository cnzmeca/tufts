# Makefile
# Christian Zinck 3/8/18
# Assignment 4: Arith
# The Makefile for the assignment

# Variables
CC = gcc
IFLAGS = -I/comp/40/include -I/usr/sup/cii40/include/cii
CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64
LDLIBS = -larith40 -l40locality -lnetpbm -lcii40 -lm
INCLUDES = $(shell echo *.h)

# Rules
all: 40image-6

# Compile
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Link
40image-6: 40image.o compress40.o ppm_ypp.o ypp_ppabcd.o ppabcd_codeword.o \
	bitpack.o uarray2.o a2plain.o
	 $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

test:	test.o bitpack.o
	 $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)
# Clean
clean:
	rm -f 40image *.o
