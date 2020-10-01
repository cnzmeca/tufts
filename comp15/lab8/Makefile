# Makefile for ImageEngine
#
CXX      = clang++
CXXFLAGS = -Wall -Wextra -Wreturn-type -std=c++11 -g
LDFLAGS  = -g

imageengine: main.o ImageEngine.o
	${CXX} ${LDFLAGS} -o ImageEngine main.o ImageEngine.o

main.o:         main.cpp ImageEngine.h
ImageEngine.o:  ImageEngine.cpp ImageEngine.h

clean:
	rm -rf ImageEngine *.o *.dSYM

provide:
	provide comp15 lab8 main.cpp ImageEngine.cpp ImageEngine.h Makefile
