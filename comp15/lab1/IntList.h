/* 
 * HookBook Social Network's PirateList's IntList
 * COMP 15  Lab 1
 */

#ifndef INTLIST_H
#define INTLIST_H


class IntList
{

public:
        IntList();   /* Constructor */
        ~IntList();  /* Destructor */

        /* The function you will write
         * Add a value to the end of the sequence.
         */
        bool addAtBack(int value);

        /* 
         * Prints the values in the list.
         *
         * This method is "const", which is a promise to the compiler
         * that it won't change the value of any private variables. 
         */
        void print() const;

        /* Returns the value at the given index */
        int getAtIndex(int index);

        /* Deletes the list and frees the memory it occupied */
        void deleteList();
        
private:

        static const int INIT_CAPACITY = 5; 

        int    *intArray;
        int     intCount;
        int     intCapacity;

	void expandList();
};

#endif
