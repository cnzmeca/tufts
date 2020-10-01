# Makefile
# Christian Zinck and Phong Hoang 4/5/18
# Assignment 6: UM Design Doc
# The Makefile for the assignment

# Variables
CC = gcc
IFLAGS = -I/comp/40/include -I/usr/sup/cii40/include/cii
CFLAGS = -g -std=gnu99 -Wall -O2 -Wextra -Werror -Wfatal-errors -pedantic
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64
LDLIBS = -lnetpbm -lcii40-O2 -lm
INCLUDES = $(shell echo *.h)

# Rules
all: um

# Compile
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Link
um:   um.o segment.o sequence.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Clean
clean:
	rm -f $(EXECS) *.o

