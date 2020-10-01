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

bool Hookbook::addPirate(int memberID, string memberName)
{
        return pl.addPirate(memberID, memberName);
}

void Hookbook::print() const
{
        pl.print();
}

bool Hookbook::addFriend(int memID, int friendID)
{
        return pl.addFriend(memID, friendID);
}
