/*
 *      SequenceQueue.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation
 */

#include <iostream>
#include "SequenceQueue.h"

using namespace std;


/*
 * Default constructor:  nothing necessary.
 * Data member constructor runs automatically.
 */
SequenceQueue::SequenceQueue() 
{
        // circular sequence initialized automatically
}

/*
 * If given an initial capacity, we need to run the non-default
 * constructor for our sequence data member.
 * In C++ this is one using  something called a "member initialization
 * list," which is a bunch of initializations specified after the
 * function head and a colon and before the opening brace of the
 * function body.
 */
SequenceQueue::SequenceQueue(int initialCapacity) : queue(initialCapacity)
{
        // done in member initialization list
}

SequenceQueue::~SequenceQueue() 
{
        // nothing to do:  sequence destructor runs automatically
}

/*
 * Remove the first element in the queue and return it.
 */
ElementType SequenceQueue::dequeue() 
{
        return queue.removeFromFront();
}

/*
 * Add a new element to the back of the queue.
 */
void SequenceQueue::enqueue(ElementType element) 
{
	queue.addAtBack(element);
}

/*
 * Print the contents of the queue in order.
 */
void SequenceQueue::printQueue() 
{
        queue.printSequence();
}
