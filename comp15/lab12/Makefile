#
# Makefile for Graph Traversal Lab
#
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS  = -g3

graphTraversal: main.o graph.o
	${CXX} ${LDFLAGS} -o graphTraversal graph.o main.o

main.o:   main.cpp graph.h
graph.o:  graph.cpp graph.h

clean:
	rm -rf graphTraversal *.dSYM *.o

provide:
	provide comp15 lab12 main.cpp graph.cpp graph.h Makefile
