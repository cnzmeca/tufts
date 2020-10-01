/*
Christian Zinck
HW3
9/30/17
*/
#ifndef CHECKOUTQUEUE_H
#define CHECKOUTQUEUE_H
#include "shopper.h"

class CheckoutQueue
{
public:
	CheckoutQueue();
	~CheckoutQueue();
	
	bool isEmpty();
	int size();
	int totalItems();
	void enqueue(Shopper shop);
	void dequeue();
	Shopper *front();

	// void print(); // used as public during testing
private:
	int count;
	int capacity;
	Shopper *queue;
	
	void print();
	void expand();
}; 

#endif
