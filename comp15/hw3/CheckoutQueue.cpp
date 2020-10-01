/*
Christian Zinck
HW3
9/30/17
*/

#include <iostream>
#include "CheckoutQueue.h"
#include "shopper.h"

using namespace std;

// Default Constructor
CheckoutQueue::CheckoutQueue()
{
	count = 0;
	capacity = 10;
	queue = new Shopper[10];
}

// Destructor 
CheckoutQueue::~CheckoutQueue()
{
	delete [] queue;
}

// Checks if queue is empty
bool CheckoutQueue::isEmpty()
{
	return count == 0;
}

// Returns size of queue
int CheckoutQueue::size()
{
	return count;
}

// Returns total number of items among all shoppers in queue
int CheckoutQueue::totalItems()
{
	int total = 0;
	for (int i = 0; i < count; i++)
	{
		total += queue[i].items_left;
	}
	return total;
}

// Adds a shopper to the end of the queue
void CheckoutQueue::enqueue(Shopper shop)
{
	if (count >= capacity)
		expand();
	queue[count] = shop;
	count++;
}

// Removes the first shopper in queue
void CheckoutQueue::dequeue()
{
	if (count == 0)
		throw runtime_error("empty_queue");
	for (int i = 0; i < count-1; i++)
	{
		queue[i] = queue[i+1];
	}
	count--;
}

// Returns a pointer to first shopper in queue
Shopper *CheckoutQueue::front()
{
	if (count == 0)
                throw runtime_error("empty_queue");
	return &queue[0];
}

// Prints all shoppers in queue
void CheckoutQueue::print()
{
	for (int i = 0; i < count; i++)
	{
		Shopper curr = queue[i];
		cout << "Shopper #" << curr.id << " arrived at " <<
		curr.arrival_time << " with " << curr.num_items <<
		" items and has " << curr.items_left << " items remaining.\n";
	}
}

// Doubles size of queue
void CheckoutQueue::expand()
{
	capacity *= 2;
        Shopper *temp = new Shopper[capacity];
        for (int i = 0; i < capacity/2; i++)
                temp[i] = queue[i];
        delete [] queue;
        queue = temp;
}
