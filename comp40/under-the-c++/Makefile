###
### Makefile for Comp 40 Lab 0:  Under the C++
###
### Instructions:  Fill out this file so that you can use
###                make to build the lab programs.
###
### Recommendation:  You don't have worry about variables right now.
###                  - For each executable, make a rule that builds the
###                    executable from a .o file.
###                  - For each .o file, make a rule that builds the .o
###                    file from a .c file.
###                  - If you have time, you can rewrite things using
###                    variables and implicit rules later.

all:  print_args simplecalc bettercalc

clean:
	rm -rf print_args simplecalc bettercalc
print_args.o:	print_args.c
	gcc -c print_args.c -o print_args.o
print_args:	print_args.o
	gcc print_args.o -o print_args
simplecalc.o:	simplecalc.c
	gcc -c simplecalc.c -o simplecalc.o
simplecalc:	simplecalc.o
	gcc -o simplecalc simplecalc.o
bettercalc.o:	bettercalc.c
	gcc -c bettercalc.c -o bettercalc.o
bettercalc:	bettercalc.o
	gcc -o bettercalc bettercalc.o
