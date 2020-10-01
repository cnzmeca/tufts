/*
 *      CircularSequence.h 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      A class that represents an ordered sequence of elements.  This
 *      one is for strings.
 *      
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon, Tufts University
 *                 Added documentation and nextIndex() function.
 */


#ifndef CIRCULAR_SEQUENCE_H
#define CIRCULAR_SEQUENCE_H

/*
 * The following defines a type called ElementType that is a synonym
 * for string.  In principle, we could change the definition to
 * another type, and just recompile for lists of that type.
 */
typedef std::string ElementType;

class CircularSequence
{
public:
        CircularSequence();     
        CircularSequence(int givenCapcity); 
        ~CircularSequence(); 

        bool        addAtBack(ElementType elem);
        bool        addAtFront(ElementType elem);
        ElementType removeFromBack();
        ElementType removeFromFront();

        void        printSequence();

private:
        static const int INIT_CAPACITY = 5;

        ElementType     *sequenceArray;
        int              currentSize;
        int              capacity;
        int              front;
        int              back;

        int  nextIndex(int index);
        int  prevIndex(int index);
	void expand();
        void init(int givenCapacity);
};

#endif
