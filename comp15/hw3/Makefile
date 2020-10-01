CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS = -g3

grocerySim: GrocerySim.o CheckoutQueue.o main.o
	${CXX} ${LDFLAGS} -o grocerySim	GrocerySim.o	CheckoutQueue.o	main.o

GrocerySim.o: GrocerySim.cpp GrocerySim.h
CheckoutQueue.o: CheckoutQueue.cpp CheckoutQueue.h
main.o: main.cpp

clean:
	rm -rf grocerySim *.o *.dSYM

provide:
	provide comp15 hw3 CheckoutQueue.h CheckoutQueue.cpp \
	testCheckoutQueue.cpp GrocerySim.h \
	GrocerySim.cpp main.cpp shopper.h \
	README Makefile
