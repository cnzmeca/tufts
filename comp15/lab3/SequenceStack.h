/*
 *      SequenceStack.h 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      A class that represents a stack of elements.
 *      The type ElementType is presumed to be defined before this
 *      file is included.
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation and include guards
 */
#ifndef SEQUENCE_STACK_H
#define SEQUENCE_STACK_H

#include "CircularSequence.h"

class SequenceStack 
{
public:
        SequenceStack();
        SequenceStack(int capacity);
        ~SequenceStack();

        ElementType pop();
        ElementType top();
        void        push(ElementType element);

        void        printStack();

private:
        CircularSequence stack;
};

#endif
