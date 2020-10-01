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
all: test

# Compile
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Link

test:   test.o phases.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)
# Clean
clean:
	rm -f test *.o               
