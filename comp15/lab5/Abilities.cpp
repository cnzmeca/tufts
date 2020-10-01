/*
 * Abilities.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: Chris Gregg
 *
 *  Changelog:
 *    2015-10-11 [msheldon] changed 'head' to 'front'
 *                          some reformatting
 *    2016-02-28 [msheldon] separated out a function to initialize a new
 *                          AbilityNode.  Could have added a constructor
 *                          for AbilityNodes.
 *    2016-10-01 [yjun01]   Changed class name to AbilityList
 *                          Students found too many things called 
 *                          "ability" or "abilities" confusing.
 */

#include <iostream>

#include "Abilities.h"

using namespace std;

//
// Allocate and initialize a new AbilityNode
// and return pointer to new node
//
AbilityList::AbilityNode *AbilityList::newAbilityNode(string weapon,
                                                      int strength,
                                                      AbilityNode *nextNode)
        const
{
        AbilityNode *newNode      = new AbilityNode();
	newNode->ability.weapon   = weapon;
        newNode->ability.strength = strength;
        newNode->next             = nextNode;
	return newNode;
}


AbilityList::AbilityList()
{
	// start with only your hand
	front = newAbilityNode("hand", 1, NULL);
}

// copy constructor
AbilityList::AbilityList(const AbilityList &source)
{
	front = copyList(source.front, front);
}


// assignment (=) overload
AbilityList &AbilityList::operator=(const AbilityList &source)
{
	if (this != &source)
	{
		deleteList();
		front = copyList(source.front, front);
	}
	return *this;
}

AbilityList::~AbilityList()
{
	deleteList();
}

void AbilityList::deleteList()
{
	AbilityNode *temp = front;
	while (front != NULL)
	{
		temp = front->next;
		delete [] front;
		front = temp;
	}
}


AbilityList::AbilityNode *AbilityList::copyList(AbilityNode *first, AbilityNode *firstcp)
{
	string w = first->ability.weapon;
	int s = first->ability.strength;
	if (first->next == NULL)
		return newAbilityNode(w,s,NULL);
	else
		return newAbilityNode(w,s,copyList(firstcp->next));
}


void AbilityList::updateAbility(std::string name, int amount)
{
	AbilityNode *curr = front;
	AbilityNode *prev = NULL;

	while (curr != NULL) {
		if (curr->ability.weapon == name) {
			// found the node to update
			curr->ability.strength = amount;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	// not found, create new node to populate
	curr = newAbilityNode(name, amount, NULL);

	if (prev == NULL) {     // if at front
		front = curr;
	} else {
		prev->next = curr;
	}
}

int AbilityList::getStrength(std::string name) const
{
	// returns -1 if the name does not exist in the list
	AbilityNode *curr = front;
	while (curr != NULL) {
		if (curr->ability.weapon == name) {
			return curr->ability.strength;
		}
		curr = curr->next;
	}
	return -1;
}

int AbilityList::abilityCount() const
{
	AbilityNode *curr = front;
	int count = 0;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;
}

Ability &AbilityList::abilityByIndex(int index) const
{
	// does not do error checking on index!
	AbilityNode *curr = front;
	for (int i = 0; i < index;i++) {
		curr = curr->next;
	}
	return curr->ability;
}

void AbilityList::printAbilityList() const
{
	// walk the list and print all weapons and abilities
	AbilityNode *curr = front;
	while (curr != NULL) {
		cout << "\t" << curr->ability.weapon << " : "
				<< curr->ability.strength << "\n";
		curr = curr->next;
	}
}

int AbilityList::totalStrength() const
{
	int totalStrength = 0;

	// walk the list and calculate total strength
	AbilityNode *curr = front;
	while (curr != NULL) {
		totalStrength += curr->ability.strength;
		curr = curr->next;
	}
	return totalStrength;
}
