/*
Christian Zinck
10/13/17
Project 1
Member functions and data for DatumStack class
*/
#include "Datum.h"
#include "DatumStack.h"

#include <iostream>

using namespace std;

// Default Constructor
DatumStack::DatumStack()
{
	count = 0;
	capacity = 50;
	s = new DatumElement[50];
}

// Array Constructor
DatumStack::DatumStack(Datum arr[], int length)
{
	count = length;
	capacity = length;
	s = new DatumElement[length];
	for (int i = 0; i < length; i++)
		s[i] = DatumElement(arr[i]);
	
}

// Destructor
DatumStack::~DatumStack()
{
	delete [] s;
}

// Returns true if stack is empty and takes no parameters.
bool DatumStack::isEmpty()
{
	return (count == 0);
}

// Clears stack. Returns void and takes no parameters.
void DatumStack::clear()
{
	count = 0;
}

// Returns stack size and takes no parameters.
int DatumStack::size()
{
	return count;
}

// Returns top Datum on stack and takes no parameters.
Datum DatumStack::top()
{
	if (isEmpty())
		throw runtime_error("empty_stack");
	return s[count-1].element;
}

// Removes top element on stack. Returns void and takes no parameters.
void DatumStack::pop()
{
	if (isEmpty())
		throw runtime_error("empty_stack");
	count--;
}

// Adds parameter d to the stack. Returns void.
void DatumStack::push(Datum d)
{
	s[count] = DatumElement(d);
	count++;
}

// Prints stack. Returns void and takes no parameters.
void DatumStack::print()
{
	if (isEmpty())
		cout << "Empty";
	for (int i = 0; i < count; i++)
		cout << s[i].element.toString() << " ";
	cout << endl;
}
