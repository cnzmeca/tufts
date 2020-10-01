/*
 *      CircularSequence.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Documentation added by Mark A. Sheldon, Tufts University
 */

#include <iostream>
#include <stdexcept>

#include "CircularSequence.h"


using namespace std;


/*
 * Return the index of the next element in the sequence.
 * Wraps around!
 */
int CircularSequence::nextIndex(int index)
{
        return (index+1) % capacity;
}

int CircularSequence::prevIndex(int index)
{
	return (index+capacity-1) % capacity;
}
/* Default Constructor */
CircularSequence::CircularSequence()
{
        init(INIT_CAPACITY);
}

/* 
 * Overloaded Constructor for a sequence with a hint for an initial
 * capacity. 
 */
CircularSequence::CircularSequence(int initialCapacity)
{
        init(initialCapacity);
}

/*
 * Initialize a new, empty sequence with an initial capacity.
 */
void CircularSequence::init(int initialCapacity)
{
        capacity      = initialCapacity;
        sequenceArray = new ElementType[capacity];
        currentSize   = 0;
        front         = 0;
        back          = 0;
}

/*
 * Destructor:  recycles the dynamically allocated array containing
 * the data.
 */
CircularSequence::~CircularSequence()
{
        delete [] sequenceArray;
}

/* 
 *  Add given element to the back of the list (at element
 *  currentSize). 
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtBack(ElementType elem) 
{
        if (currentSize == capacity) {
                expand();
        }
        sequenceArray[back] = elem;
        back                = nextIndex(back);
        currentSize++;

        return true;
}

/* 
 *  Add given element to the front of the list (at element 0)
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtFront(ElementType elem)
{
        if (currentSize == capacity)
		expand();
	if(currentSize == 0)
		sequenceArray[0] = elem;
	else
	{
		front = prevIndex(front);
		sequenceArray[front] = elem;
	}

	currentSize++;
	return true;
}
                
/*
 * Remove the element at the back of the list (index currentSize - 1)
 * and return it.
 */
ElementType CircularSequence::removeFromBack() 
{
        back = prevIndex(back);
	currentSize--;
	return sequenceArray[back];
}
 
/*
 * Remove the element at the front of the list (element 0)
 * and return it.
 */
ElementType CircularSequence::removeFromFront()
{
	front = nextIndex(front);
	currentSize--;
	return sequenceArray[prevIndex(front)];
}

/*
 * Expand the capacity of the array by a factor of 2.
 */
void CircularSequence::expand() 
{
	ElementType *temp = new ElementType[capacity*2];
        int currIndex = front;
	for (int i = 0; i < currentSize; i++)
	{
		temp[i] = sequenceArray[currIndex];
		currIndex = nextIndex(currIndex);
	}

	delete [] sequenceArray;
	sequenceArray = temp;
	
	front = 0;
	back = currentSize;
	capacity *= 2;
	
}

/*
 * Print the contents of the sequence, one element per line.
 */
void CircularSequence::printSequence() 
{
        int currIndex = front;
        for (int i = 0; i < currentSize; i++) {
                cout << sequenceArray[currIndex] << endl;
                currIndex = nextIndex(currIndex);
        }
}
