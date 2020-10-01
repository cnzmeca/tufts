CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS = -g3

CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o
	${CXX} ${LDFLAGS} -o CalcYouLater main.o RPNCalc.o DatumStack.o \
								Datum.o
Datum.o: Datum.h
RPNCalc.o: RPNCalc.cpp RPNCalc.h
DatumStack.o: DatumStack.cpp DatumStack.h
main.o: main.cpp

clean:
	rm -rf CalcYouLater *.o *.dSYM

provide:
	provide comp15 proj1 DatumStack.h DatumStack.cpp \
	testDatumStack.cpp RPNCalc.h RPNCalc.cpp \
	testRPNCalc.cpp main.cpp README Makefile                   
