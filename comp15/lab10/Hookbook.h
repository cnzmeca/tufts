/* 
 * HookBook Social Network
 * COMP 15  Lab 1
 */

#ifndef HOOKBOOK_H
#define HOOKBOOK_H

#include "Sequence.h"

class Hookbook
{

public:
        Hookbook();
        ~Hookbook();

        /* 
         * Adds a new pirate to PirateList.
         * The pirate starts out with no friends.
         * Return false if memberID is in use.
         * Calls PirateList's addPirate function
         */
        bool addPirate(int memberID, std::string memberName);


        /* Add a new friend to memID's friend list.
         * Return false if there is no pirate with ID memID
         * Calls PirateList's addFriend function
         */
        bool addFriend(int memID, int friendID);

        /* 
         * Prints the values in the list in ascending order.
         *
         */
        void print();
    
private:
        struct Pirate
        {
                int           memberID;
                std::string   name;
                Sequence<int> friendList;
        };

        Sequence<Pirate> pirates;

        int  pirateIndex(int memberID);
        void printFriends(Pirate &p);
};

#endif
