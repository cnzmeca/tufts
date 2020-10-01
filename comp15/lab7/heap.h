/*
 * Comp 15:  Heap lab
 *
 * A class that organizes a collection of strings into a min-heap
 *
 * O(n log(n)) construction, 
 * O(1)        to access minimum element
 * O(log(n))   to remove minimum element.
 */

#include <string>

using std::string;

class Heap 
{
public:
	Heap();
	~Heap(); 

	// Build a heap from array
	Heap(string list[], int listSize);

        // insert s into heap, not used for this lab
	void insert(string s);

        // return minimum element, not used for this lab
        string min();

	// remove and return smallest element in heap
	string removeMin();

	// return size of heap;
	int size();

private:
	// Heap is implemented as a dynamic array
        static const int INIT_SIZE = 100;

	string *heap;            // pointer to array with heap data
	int     heapSize;        // # elements currently in heap
	int     maxCapacity;     // current max capacity

        //
	// down heap function is recursive and
	// works with the location of the element
	// in the tree.  heap[location] stores
	// the value being inserted
        //
	void downHeap(int location);

        //
	// up heap function for insert
	// since it is an array it must
	// add to the tree at the last empty slot
	// and the added element percolates up to the
	// proper spot
        //
	void upHeap(int location); 

        //
	// build heap function used by constructor that takes in an array
	// and turns the array into a heap (aka "heapify")
        //
	void buildHeap();

        //
	// getter methods to determine which/where child/parent
	// relationships
        //
	int  leftChild(int index);
	int  rightChild(int index);
	int  parent(int index);

	void ensureCapacity(int desiredCapacity);
};
