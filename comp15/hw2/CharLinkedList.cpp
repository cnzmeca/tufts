/*
 *
 *  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in hur
 *
 *  CharLinkedList.cpp
 *  Complete CharLinkedList Class Implementation
 *  Modified By (UTLN): czinck01
 *           On       : 9/22/17
 *
 */

#include <iostream>

#include "CharLinkedList.h"

using namespace std;

// No args constructor
CharLinkedList::CharLinkedList()
{
	front = nullptr;
	back = nullptr;
}

// Single node constructor
CharLinkedList::CharLinkedList(char letter)
{
	insertIntoEmpty(letter);
}

// Multinode constructor
CharLinkedList::CharLinkedList(char arr[], int size)
{
	front = nullptr;
	for (int i = 0; i < size; i++)
	{
		pushAtBack(arr[i]);
	}
}

// Destructor
CharLinkedList::~CharLinkedList()
{
	CharNode *currNode = front;
	while (currNode != nullptr)
	{
		CharNode *nextNode = currNode->next;
		delete [] currNode;
		currNode = nextNode;
	}	
}

// Checks if list is empty
bool CharLinkedList::isEmpty()
{
	return front == nullptr;
}

// Clears the list to an empty list
void CharLinkedList::clear()
{
	CharNode *currNode = front;
        while (currNode != nullptr)
        {
                CharNode *nextNode = currNode->next;
                delete [] currNode;
                currNode = nextNode;
        }
	front = back = nullptr;
}

// Returns size of the list
int CharLinkedList::size()
{
	int size = 0;
	CharNode * currNode = front;
	while (currNode != nullptr)
	{
		currNode = currNode->next;
		size++;
	}
	return size;
}

// Returns first char in list
char CharLinkedList::first()https://stackoverflow.com/questions/255612/dynamically-allocating-an-array-of-objects
{
	if (isEmpty())
                throw runtime_error("list_is_empty");
	return front->element;
}

// Returns last char in list
char CharLinkedList::last()
{
	if (isEmpty())
                throw runtime_error("list_is_empty");
	return back->element;
}

// Returns the element at the specified index
char CharLinkedList::elementAt(int index)
{
	CharNode * currNode = front;
	for (int i = 0; i < index; i++)
	{
		if (currNode->next == nullptr)
			throw range_error("index_out_of_range");
		currNode = currNode->next;
	}
	return currNode->element;
}

// Prints the list in the correct format
void CharLinkedList::print()
{
	cout << "[CharLinkedList of size " << size() << " <<";
	
	CharNode * currNode = front;
	while (currNode != nullptr)
	{
		cout << currNode->element;
		currNode = currNode->next;
	}

	cout << ">>]" << endl;
}

// Adds the specified letter to the end of the list
void CharLinkedList::pushAtBack(char letter)
{https://stackoverflow.com/questions/255612/dynamically-allocating-an-array-of-objects
	if (isEmpty())
		insertIntoEmpty(letter);
	else
	{
		CharNode *temp = newCharNode(letter);
		back->next = temp;
		temp->prev = back;
		back = temp;
	}
}

// Adds the specified letter to the front of the list
void CharLinkedList::pushAtFront(char letter)
{
	if (isEmpty())
		insertIntoEmpty(letter);
	else
	{
		CharNode *temp = newCharNode(letter);
		front->prev = temp;
		temp->next = front;
		front = temp;
	}
}

// Inserts the specified letter at the specified index
void CharLinkedList::insertAt(char letter, int index)
{
	CharNode * currNode = front;
        for (int i = 0; i < index; i++)
        {
                if (currNode->next == nullptr)
                        throw range_error("index_out_of_range");
                currNode = currNode->next;
        }
	CharNode *temp = newCharNode(letter);
	temp->prev = currNode->prev;
	temp->next = currNode;
	temp->prev->next = temp;
	currNode->prev = temp;
}

// Inserts the specified letter in alphabetical order
void CharLinkedList::insertInOrder(char letter)
{
	if (isEmpty())
		insertIntoEmpty(letter);
	else
	{
		CharNode * currNode = front;
		for (int i = 0; i < size(); i++)
		{
			if (i == 0)
			{
				if (letter < currNode->element)
				{
					pushAtFront(letter);
					break;
				}
			}
			else if (i == size() - 1)
			{
				pushAtBack(letter);
				break;
			}
			else
			{
				if (letter < currNode->element)
				{
					insertAt(letter, i);
					break;
				}
			}
			currNode = currNode->next;
		}
	}
}

// Removes the first element from the list
void CharLinkedList::popFromFront()
{
	if (isEmpty())
		://stackoverflow.com/questions/255612/dynamically-allocating-an-array-of-objectsthrow runtime_error("list_is_empty");
	CharNode *temp = front;
	front = front->next;
	front->prev = nullptr;
	delete [] temp;
	
}
// Removes the last element from the list
void CharLinkedList::popFromBack()
{
	if (isEmpty())
                throw runtime_error("list_is_empty");
	CharNode *temp = back;
	back = back->prev;
	back->next = nullptr;
	delete [] temp;
}

// Removes the element at the specified index
void CharLinkedList::removeAt(int index)
{
	CharNode *currNode = front;
	for (int i = 0; i < index; i++)
        {
                if (currNode->next == nullptr)
                        throw range_error("index_out_of_range");
                currNode = currNode->next;
        }
	currNode->prev->next = currNode->next;
	currNode->next->prev = currNode->prev;
	delete [] currNode;
}

// Replaces the element at the specified index with the specified letter
void CharLinkedList::replaceAt(char letter, int index)
{
	CharNode *currNode = front;
        for (int i = 0; i < index; i++)
        {
                if (currNode->next == nullptr)
                        throw range_error("index_out_of_range");
                currNode = currNode->next;
        }
	currNode->element = letter;
}

// Concatenates the caller list with the list determined by the given pointer
void CharLinkedList::concatenate(CharLinkedList *secondList)
{
	back->next = secondList->front;
	secondList->front->prev = back;
	back = secondList->back;
}

// Makes the list a singly linked list to conserve memory
void CharLinkedList::shrink()
{
	CharNode *currNode = front;
	while (currNode != nullptr)
	{
		currNode->prev = nullptr;
		currNode = currNode->next;
	}
	back = nullptr;
}

// Returns true if the specified letter exists in the list
bool CharLinkedList::find(char letter)
{
	CharNode *currNode = front;
	while (currNode != nullptr)
        {
		if (currNode->element == letter)
			return true;
                currNode = currNode->next;
        }
	return false;
}

// Creates a CharNode with the specified char as its element value
CharLinkedList::CharNode *CharLinkedList::newCharNode(char letter)
{
	CharNode *newNode = new CharNode;
	newNode->element = letter;
	newNode->prev = nullptr;
	newNode->next = nullptr;
	return newNode;
}

// Inserts a char into an empty list
void CharLinkedList::insertIntoEmpty(char letter)
{
	front = newCharNode(letter);
	back = front;
}https://stackoverflow.com/questions/255612/dynamically-allocating-an-array-of-objects
