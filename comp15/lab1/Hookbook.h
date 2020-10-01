/* 
 * HookBook Social Network
 * COMP 15  Lab 1
 */

#ifndef HOOKBOOK_H
#define HOOKBOOK_H

#include "PirateList.h"

class Hookbook
{

public:
        Hookbook();   /* constructor */

        /* 
         * Adds a new pirate to PirateList.
         * The pirate starts out with no friends.
         * Return false if memberID is in use.
         * Calls PirateList's addPirate function
         */
        bool addPirate(int memberID, std::string memberName);

        /* 
         * Prints the values in the list in ascending order.
         *
         * This method is "const", which is a promise to the compiler
         * that it won't change the value of any private variables.
         * Calls PirateList's print function
         */
        void print() const;

        /* Add a new friend to memID's friend list.
         * Return false if there is no pirate with ID memID
         * Calls PirateList's addFriend function
         */
        bool addFriend(int memID, int friendID);
    
        ~Hookbook();   /* destructor */
        
private:

        PirateList pl;
};

#endif
