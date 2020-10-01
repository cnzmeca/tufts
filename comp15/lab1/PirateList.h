/* 
 * HookBook Social Network's PirateList
 * COMP 15  Lab 1
 */

#ifndef PIRATELIST_H
#define PIRATELIST_H

#include "IntList.h"

class PirateList
{

public:
        PirateList();   /* constructor */

        /* 
         * The function you will write
         * Return false if memberID is in use.
         * Otherwise, adds a new pirate to PirateList and returns true.
         */
        bool addPirate(int memberID, std::string memberName);

        /* 
         * Prints the values in the list in ascending order.
         *
         * This method is "const", which is a promise to the compiler
         * that it won't change the value of any private variables. 
         * Calls IntList's print function
         */
        void print() const;

        /* Add a new friend to memID's friend list.
         * Return false if there is no pirate with ID memID
         * Calls IntList's addFriend function
         */
        bool addFriend(int memID, int friendID);
    
        ~PirateList();   /* destructor */
        
private:
        struct Pirate
        {
                int          memberID;
                std::string  name;
                IntList     *friendList;
        };

        static const int INIT_CAPACITY = 5; 

        Pirate *pirateArray;
        int     pirateCount;
        int     pirateCapacity;

        void    initializePirate(int         pirateCount,
                                 int         memberID,
                                 std::string memberName);

        int     pirateIndex(int memID);
	void	expandList();
};

#endif
