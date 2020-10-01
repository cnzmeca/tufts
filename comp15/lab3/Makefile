#
# Makefile for partyPlaylist
#

#
# We'll first define some variables.  You can define any variables you
# like, but there are some variables that have conventional meanings.
#
# CXX is conventionally used for the C++ compiler you want to use.  
# We'll use clang++ in Comp 15, because it tends to have better error
# messages than the alternative (g++).  CPP wasn't used for C++, because
# it was already in use for something else when C++ was invented.
#
# CXXFLAGS is conventionally used for the parameters (flags) you want 
# to use whenever you compile a C++ program.  In this case, we're
# telling the compiler to leave all the debugging information it can
# in the resulting file (g3), to give us all the standard warnings
# (Wall), and to give us even MORE warnings (Wextra).
#
# LDFLAGS is conventionally used for the parameters (flags) you want
# to use when you link a bunch of program components together to make
# an executable program.  In this case, we're asking for all the
# debuggin information again.
#
CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra
LDFLAGS  = -g3


#
# Here are the rules!  Each rule has a "target" followed by a colon.
# After the colon, is a list of "dependencies" (also called
# "prerequisites") all on one line.  These are files that must already
# exist and be up-to-date before you can make the target.  So, the
# first rule below says that you'd like define how to make a thing
# called "peanutOlympics," and that depends on 4 .o files.  You may follow
# that line with a recipe as a series of one line commands indented
# with a tab character (yes, it must be a tab character!).  In this
# first rule, if you have all the .o files up-to-date, you make a
# peanutOlympics by running clang++ with the flags specified above giving it
# all the .o files and producing leaving the executable output in a
# file named "peanutOlympics."
# 
#
partyPlaylist: CircularSequence.o SequenceStack.o SequenceQueue.o main.o
	${CXX} ${LDFLAGS} -o partyPlaylist CircularSequence.o SequenceStack.o \
                                       SequenceQueue.o main.o


#
# The following rules don't have recipes.  The make program has a ton
# of built-in rules, and it knows that if you want a X.o file and you
# have an X.cpp, it can compile the .cpp file to make a .o file.
# Furthermore, if the conventionally known variables CXX and CXXFLAGS
# are defined, it will use them!  What it doesn't know is what files
# besides the .cpp file the program module might depend on.  So, we
# only specify the target and dependencies here.  We could also
# specify the recipe like this:
#
# peanutOlympics.o:  peanutOlympics.cpp RunList.h
# 	${CXX} ${CXXFLAGS} -c -o peanutOlympics.o peanutOlympics.cpp
#
# which is exactly what will happen with the rules as specified.
#

CircularSequence.o: CircularSequence.cpp 
SequenceStack.o:    SequenceStack.cpp    SequenceStack.h   CircularSequence.h
SequenceQueue.o:    SequenceQueue.cpp    SequenceQueue.h   CircularSequence.h
main.o:             main.cpp             SequenceStack.h   SequenceQueue.h     \
                    CircularSequence.h

#
# The following rules show how you can use make to automate things
# besides program building.
#
# Makefiles traditionally have a "clean" target.  The purpose is to
# clean up everything that is automatically built by make.  It's
# useful for when you want to save disk space and also when you've
# messed things up and just want to rebuild everything from scratch.
# The clean target doesn't have an prerequisites, because you don't
# need anything to be there in order to clean up!
#
# .dSYM directories are something that gets make in the Mac
# environment for debugging data, and so I delete them when cleaning
# up. 
#
clean:
	rm -rf partyPlaylist *.dSYM *.o

#
# You can even have a rule that turns your work in for you!
# You can make rules for running tests, too.
#
provide:
	provide comp15 lab3 CircularSequence.cpp CircularSequence.h \
			SequenceQueue.cpp SequenceQueue.h           \
			SequenceStack.cpp SequenceStack.h Makefile
