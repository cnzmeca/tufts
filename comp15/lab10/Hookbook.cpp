/*
 * Comp 15 Lab 1
 * Sequences
 * Solution
 *
 * Mark A. Sheldon and Erica Schwartz
 * based on prior versions by Chris Gregg
 */

#include <iostream>
#include <string>

#include "Hookbook.h"

using namespace std;

Hookbook::Hookbook()
{
        // nothing to be done
}

Hookbook::~Hookbook()
{
        // nothing to be done
}

/* Add a new prirate to the Hookbook.
 * Return false if we already have a pirate with given ID.
 * Return true after successfully adding the pirate.
 */
bool Hookbook::addPirate(int memberID, string memberName)
{
        if (pirateIndex(memberID) != -1)   /* ensure ID not in use */
                return false;
	Pirate temp;
	temp.memberID = memberID;
	temp.name = memberName;
	temp.friendList	= Sequence<int>();
	pirates.addAtBack(temp);
        return true;
}

/*
 * Print the Hookbook
 */
void Hookbook::print()
{
        cout << "There are " << pirates.size()
             << " pirates in the system." << endl;

        for (int i = 0; i < pirates.size(); ++i) {
                cout << "Pirate: "         << pirates[i].name
                     << " with memberID: " << pirates[i].memberID
                     << " has friends ";
        
                printFriends(pirates[i]);
                cout << endl;
        }

}

/*
 * Print pirate's friends list all on one line
 */
void Hookbook::printFriends(Pirate &p)
{
        for (int i = 0; i < p.friendList.size(); ++i)
                cout << p.friendList[i] << " ";
}

/*
 * Add a new friend to the friend list for pirate with given ID
 * Returns false if successful and false if no pirate exists with ID.
 */
bool Hookbook::addFriend(int memID, int friendID)
{
        int pirateIdx = pirateIndex(memID);

        if (pirateIdx == -1)  // Pirate not found
                return false;

        pirates[memID].friendList.addAtBack(friendID);
        
        return true;
}

/*
 * Return the index of the pirate with the given ID
 * Return -1 ID not found
 */
int Hookbook::pirateIndex(int memberID)
{
        for (int i = 0; i < pirates.size(); ++i)
                if (pirates[i].memberID == memberID)
                        return i;
        return -1;
}
