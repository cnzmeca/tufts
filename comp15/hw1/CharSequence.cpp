/*
 *
 *  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
 *
 *  CharSequence.cpp
 *  Complete SequenceA Class Implementation
 *  Modified By (UTLN): czinck01
 *           On       : 9/15/17
 *
 */

#include <string>
#include <iostream>

#include "CharSequence.h"

using namespace std;

// Default Constructor
CharSequence::CharSequence()
{
	count = 0;
	capacity = 0;
	sequence = new char[0];
}

// Single Character Constructor
CharSequence::CharSequence(char letter)
{
	count = 1;
	capacity = 1;
	sequence = new char[1];
	sequence[0] = letter;
}

// Character Array Constructor
CharSequence::CharSequence(char arr[], int size)
{
	count = size;
	capacity = size;
	sequence = new char[size];
	for (int i = 0; i < size; i++)
	{
		sequence[i] = arr[i];
	}
}

// Destructor
CharSequence::~CharSequence()
{
	delete [] sequence;
}

// Returns true if sequence is empty
bool CharSequence::isEmpty()
{
	return count == 0;
}

// Clears the sequence
void CharSequence::clear()
{
	resize(0);
	count = 0;
}

// Returns the size of the sequence
int CharSequence::size()
{
	return count;
}

// Returns the first character of the sequence
char CharSequence::first()
{
	if (count == 0)
		throw runtime_error("sequence_is_empty");
	return sequence[0];
}

// Returns the last character of the sequence
char CharSequence::last()
{
	if (count == 0)
                throw runtime_error("sequence_is_empty");
	return sequence[count-1];
}

// Returns the character at the specified index
char CharSequence::elementAt(int index)
{
	if (index < 0 || index >= count)
		throw range_error("index_out_of_range");
	return sequence[index];
}

// Prints the sequence in the correct format
void CharSequence::print()
{
	cout << "[CharSequence of size " << count << " <<";
	for (int i = 0; i < count; i++)
	{
		cout << sequence[i];
	}
	cout << ">>]\n";
}

// Adds a character to the end of the sequence
void CharSequence::pushAtBack(char letter)
{
	expand();
	sequence[count] = letter;
	count++;
}

// Adds a character to the front of the sequence
void CharSequence::pushAtFront(char letter)
{
	expand();
	shiftUp(0);
	sequence[0] = letter;
	count++;	
}

// Inserts a character in the sequence at a specified index
void CharSequence::insertAt(char letter, int index)
{
	if (index > count || index < 0)
		throw range_error("index_out_of_range");
	expand();
	shiftUp(index);
        sequence[index] = letter;
	count++;
}

// Inserts a character in the sequence after the first character with lower
// ASCII value
void CharSequence::insertInOrder(char letter)
{
	expand();
	int index = 0;
	for (int i = 0; i < count+1; i++)
	{
		if (letter >= sequence[i])
			index = i;
	}
	
	shiftUp(index);
	sequence[index] = letter;
	count++;
}

// Removes the first character from the sequence
void CharSequence::popFromFront()
{
	if (count == 0)
                throw runtime_error("sequence_is_empty");
	shiftDown(0);
	count--;
	shrink();
}

// Removes the last character from the sequence
void CharSequence::popFromBack()
{
	if (count == 0)
                throw runtime_error("sequence_is_empty");
	count--;
	shrink();
}

// Removes a character from the sequence at the specified index
void CharSequence::removeAt(int index)
{
	if (index >= count || index < 0)
		throw range_error("index_out_of_range");
	shiftDown(index);
	count--;
	shrink();
}

// Replaces a character in the sequence at the specified index
void CharSequence::replaceAt(char letter, int index)
{
	if (index >= count || index < 0)
                throw range_error("index_out_of_range");
	sequence[index] = letter;
}

// Concatenates a sequence with the sequence pointed to by the parameter
void CharSequence::concatenate(CharSequence *ptr)
{
	for (int i = 0; i < ptr->count; i++)
	{
		expand();
		sequence[count] = ptr->sequence[i];
		count++;
	}
}

// Condenses a sequence so there is no unused memory
void CharSequence::shrink()
{
	resize(count);
}

// Resizes a sequence and copies as many of the values as possible, starting
// from the front of the sequence
void CharSequence::resize(int newCapacity)
{
	char *temp = new char[newCapacity];
	for (int i = 0; i < newCapacity; i++)
		temp[i] = sequence[i];
	delete [] sequence;
	sequence = temp;
	capacity = newCapacity;
}

// Expands a sequence by 2x+2 if more space is needed
void CharSequence::expand()
{
	if (count - 1 <= capacity)
		resize(2*capacity + 2);
}

// Shifts every element in the sequence up starting at the specified index
void CharSequence::shiftUp(int index)
{
	for (int i = count; i > index; i--)
	{
                sequence[i] = sequence[i-1];
	}
}

// Shifts every element in the sequence down starting at the specified index
void CharSequence::shiftDown(int index)
{
	for (int i = index; i < count-1; i++)
		sequence[i] = sequence[i+1];
}


