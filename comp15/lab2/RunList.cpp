/*
 *  RunList.cpp
 *  PeanutOlympics
 *
 *  Lab created by Chris Gregg on 1/31/14.
 *  Interface altered by Mark A. Sheldon, Fall 2015
 *  to make node structure and associated operations private.
 *  Also did some cleaning up.
 * 
 *  Solution by Mark A. Sheldon, Tufts University, Fall 2015
 *
 *  A note about use of the RunnerNode struct:
 *
 *       The RunnerNode struct is defined inside the class and is private.
 *       Because it's private, clients can't use it.
 *       The functions that are part of the class CAN use it by just
 *       using the type.
 *
 *       However, the compiler processes function return type
 *       specifications before it processes the function name.
 *       Therefore, if a function returns a RunnerNode (or a pointer
 *       to one), the function header must say "RunList::RunnerNode"
 *       to tell the compiler the return type comes from inside the
 *       class, just as you have to say "RunList::deleteFront" to tell
 *       the compiler the function itself is inside the class.
 */

#include <iostream>

#include "assert.h"

#include "RunList.h"
#include "Runner.h"

using namespace std;


RunList::RunList()
{
        front = nullptr;
}

RunList::~RunList()
{
        while (not isEmpty())
                deleteFront();
}

/* 
 * Clear out a node.  If there's a bug, a node that
 * looks like was supposed to have been deleted.
 */
void RunList::clearNodeData(RunnerNode *aNode)
{
        aNode->aRunner.setName("");
        aNode->aRunner.setTime(-1);
        aNode->next = nullptr;
}

/* 
 * Delete the first node in the list.
 * Note:  Assumes list is non-empty.
 */
void RunList::deleteFront()
{
	RunnerNode *temp = getFront()->next;
	delete front;
	front = temp;
}

/*
 * empty list has a null front
 */
bool RunList::isEmpty()
{
        return front == nullptr;
}

RunList::RunnerNode *RunList::getFront()
{
        return front;
}

RunList::RunnerNode *RunList::getBack()
{
        RunnerNode *current = front;
        RunnerNode *prev    = NULL;

        while (current != NULL) { // while not yet at end of list
                prev = current;
                current = current->next;
        }

        return prev;
}

Runner RunList::getFirst()
{
        return getFront()->aRunner;
}

Runner RunList::getLast()
{
        return getBack()->aRunner;
}

void RunList::insertIntoEmpty(RunnerNode *newNode)
{
        front = newNode;
}


/*
 * Allocate a new RunnerNode on the heap, initialize it, 
 * and return pointer to it.
 *
 * This doesn't really need to be a member function, but it would 
 * have to be a friend otherwise.  Feel free to read up on 'friends'
 * in C++.
 */
RunList::RunnerNode *RunList::newRunnerNode(string name, int time)
{
        RunnerNode *newNode = new RunnerNode;
        Runner      newRunner(name, time);
        newNode->aRunner    = newRunner;
        newNode->next       = nullptr;
        return newNode;
}

void RunList::insertInOrder(string runnerName, int runnerTime)
{
        RunnerNode *newNode  = newRunnerNode(runnerName, runnerTime);

        if (isEmpty()) 
                insertIntoEmpty(newNode);
        else {
                // find first runner with slower time than new runner
                RunnerNode *nodeAfter = front;

                while (nodeAfter != nullptr
                       and nodeAfter->aRunner.isFasterThan(newNode->aRunner))

                        nodeAfter = nodeAfter->next;

                if (nodeAfter != nullptr)                 // If slower runner,
                        insertBefore(nodeAfter, newNode); // put new one before
                else                                      // otherwise, new one
                        insertAfter(getBack(), newNode);  // is slowest, goes
        }                                                 // at back
                
}

/*
 *  Note:  Assume list is non-empty
 */

/*

Loop implementation of insertBefore

void RunList::insertBefore(RunnerNode *aNode,
                           RunnerNode *newNode)
{
	newNode->next = aNode;

	RunnerNode *temp = front;
	while (temp->next != aNode)
		temp = temp->next;
	
	temp->next = newNode;	
}
*/

void RunList::insertBefore(RunnerNode *aNode,
			   RunnerNode *newNode)
{
	newNode->next = aNode;
	RunnerNode *temp = getTemp(aNode, front);
	temp->next = newNode;
}

/*
 *  Note:  Assume list is non-empty
 */
void RunList::insertAfter(RunnerNode *aNode,
                          RunnerNode *newNode)
{
	newNode->next = aNode->next;
	aNode->next = newNode;
}


void RunList::printList()
{
        RunnerNode *iterator = front;

        while (iterator != nullptr) {
                cout << iterator->aRunner.getName() << ": ";
                cout << iterator->aRunner.getTime() << "\n";

                iterator = iterator->next;
        }
}

RunList::RunnerNode *RunList::getTemp(RunnerNode *aNode,
				      RunnerNode *currNode)
{
	if (currNode->next == aNode)
		return currNode;
	return getTemp(aNode, currNode->next);
}

