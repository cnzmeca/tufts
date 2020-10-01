/*
 *      SequenceStack.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      Implementation of the SequenceStack class
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation
 */


#include <iostream>

#include "SequenceStack.h"

using namespace std;

/*
 * Default constructor:  nothing necessary.
 * Data member constructor runs automatically.
 */
SequenceStack::SequenceStack() 
{
	// The sequence is automatically initialized
}

/*
 * If given an initial capacity, we need to run the non-default
 * constructor for our sequence data member.
 * In C++ this is one using  something called a "member initialization
 * list," which is a bunch of initializations specified after the
 * function head and a colon and before the opening brace of the
 * function body.
 */
SequenceStack::SequenceStack(int initialCapacity) : stack(initialCapacity)
{
	// Work done in member initialization list
}

SequenceStack::~SequenceStack() 
{
        // nothing to do:  sequence destructor runs automatically
}

/*
 * Remove top element from the stack and return it.
 */
ElementType SequenceStack::pop()
{
	return stack.removeFromBack();
}

/*
 * Add given element to the top of the stack.
 */
void SequenceStack::push(ElementType element) 
{
        stack.addAtBack(element);
}

/*
 * Print contents in stack in order from top to bottom
 */
void SequenceStack::printStack() 
{
        stack.printSequence();
}
