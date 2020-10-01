/*
 *      SequenceQueue.h 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      A class that represents a queue of elements.
 *      The type ElementType is presumed to be defined before this
 *      file is included. 
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation, include guards
 *                 Removed unnecessary includes
 */

#ifndef SEQUENCE_QUEUE_H
#define SEQUENCE_QUEUE_H

#include "CircularSequence.h"

class SequenceQueue 
{
public:
        SequenceQueue();
        SequenceQueue(int initialCapacity);
        ~SequenceQueue();

        ElementType dequeue();
        void        enqueue(ElementType element);

        void        printQueue();

private:
        CircularSequence queue;
};

#endif
