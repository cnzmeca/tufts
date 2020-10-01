CXX	= clang++
CXXFLAGS = -Wall -Wextra -Wreturn-type -std=c++11 -g

alphabetizer: StringBST.o Alphabetizer.o main.o
	${CXX} ${CXXFLAGS} -o alphabetizer StringBST.o Alphabetizer.o main.o

StringBST.o: StringBST.h StringBST.cpp
Alphabetizer.o: Alphabetizer.h Alphabetizer.cpp
main.o: main.cpp

provide:
	provide comp15 hw4 testStringBST.cpp testAlphabetizer.cpp \
                            StringBST.h StringBST.cpp Alphabetizer.h \
                            Alphabetizer.cpp main.cpp Makefile README test.txt
