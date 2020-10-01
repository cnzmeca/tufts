HEADERS = \
	db.h \
	msg.h

OBJECTS = \
	db.o \
	main.o \
	msg.o

default: a8

.cpp.o: $(HEADERS)
	g++ -I/usr/include/postgresql -Wall -Wno-unused-function -c -g $< -o $@

a8: $(OBJECTS)
	g++ -L/usr/lib/x86_64-linux-gnu -Wall -Wno-unused-function $(OBJECTS) -lpq -o a8

clean:
	rm -f $(OBJECTS) a8
