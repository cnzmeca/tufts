/*
 * Abilities.h
 *
 *  Created on: Oct 17, 2014
 *      Author: Chris Gregg
 *
 *  Changelog:
 *    2015-10-11 [msheldon] Made AbilityNode private
 *    2016-02-28 [msheldon] added private function to initialize a new
 *                          AbilityNode.  Could have added a constructor
 *                          for AbilityNodes.
 *    2016-10-01 [yjun01]   Changed class name to AbilityList
 *                          Students found too many things called 
 *                          "ability" or "abilities" confusing.
 */

#ifndef ABILITIES_H_
#define ABILITIES_H_

#include <string>

// an Ability has a weapon and a strength
struct Ability {
	std::string weapon;
	int         strength;
};

// linked-list based AbilityList class
class AbilityList {
public:
	// constructor
	AbilityList();

	// copy constructor
	AbilityList(const AbilityList &source);

	// assignment (=) overload
	AbilityList &operator=(const AbilityList &source);

	// desctructor
	~AbilityList();

	// update the ability of a weapon
	void updateAbility(std::string name, int amount);

	// determine the strength of a weapon based on the name
	// returns -1 if the pirate does not have this ability
	int getStrength(std::string name) const;

	// print the abilities list for a pirate
	void printAbilityList() const;

	// return total strength: the total strength is the sum
	// of all the strengths for the pirate's weapons
	int totalStrength() const;

	// returns the number of abilities the a pirate has
	int abilityCount() const;

	// returns the ability by the index
	Ability &abilityByIndex(int index) const;

private:
	struct AbilityNode {
		Ability      ability;
		AbilityNode *next;
	};

	AbilityNode *front;  	// the front of the linked list

	void         deleteList    ();
        AbilityNode *newAbilityNode(std::string weapon, int strength,
                                    AbilityNode *nextNode) const;
	//AbilityNode *copyList(AbilityNode *first);
};

#endif
