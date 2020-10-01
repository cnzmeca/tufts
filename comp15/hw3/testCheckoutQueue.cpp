#include <iostream>
#include "CheckoutQueue.h"
#include "shopper.h"
    
using namespace std; 
int main()
{
	CheckoutQueue line;
	
	// Shopper
	Shopper a;
	a.id = 1;
	a.arrival_time = 0;
	a.num_items = 10;
	a.items_left = 10;

	// Tests every function on an empty queue
	cout << line.isEmpty(); // 1
	cout << (line.size() == 0); // 1
	cout << (line.totalItems() == 0); // 1
	//line.dequeue(); // Error
	//line.front(); // Error
	line.enqueue(a); // Adds a
	//line.print(); Used during testing

	// Tests every function on a nonempty queue
	cout << (!line.isEmpty()); // 1
	cout << (line.size() == 1); // 1
	cout << (line.totalItems() == a.num_items); // 1
	line.enqueue(*line.front()); // Adds a again
	//line.print(); // Used during testing
	line.dequeue(); // Removes first copy of a
	//line.print(); // Used during testing
	line.dequeue(); // Removes second copy of a	

}
