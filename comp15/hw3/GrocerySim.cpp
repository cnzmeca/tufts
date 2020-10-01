/*
Christian Zinck
HW3
9/30/17
*/
#include <fstream>
#include <iostream>

#include "GrocerySim.h"
#include "CheckoutQueue.h"
#include "shopper.h"

using namespace std;

// Parameterized constructor
GrocerySim::GrocerySim(int a, int b, int c)
{
	numLines = a;
	numExpLines = b;
	maxExpItems = c;

	lines = NULL;
}

// Destructor
GrocerySim::~GrocerySim()
{
	delete [] lines;
}

// Runs the simulation
void GrocerySim::run(istream &infile)
{
	// Sequence of CheckoutQueues
	lines = new CheckoutQueue[numLines + numExpLines];
	
	// Populates allShoppers with all shoppers
	int idNum = 0;
	int x, y;
	for (infile >> x >> y;(!infile.eof()); infile >> x >> y)
	{
		Shopper temp;
		temp.id = ++idNum;
		temp.arrival_time = x;
		temp.num_items = y;
		temp.items_left = y;
		allShoppers.enqueue(temp);
	}
	
	int timeUnits = 0;
	// Main simulation loop
	while (continueSim())
	{
		for (int i = 0; i < (numLines+numExpLines); i++)
		{
			// Processes first shopper in each queue
			if (!lines[i].isEmpty())
			{
				Shopper *first = lines[i].front();
				(first->items_left)--;
				
				// Prints shopper when done
				if (first->items_left == 0)
				{
					cout << "Shopper " << first->id <<
					" arrived at " << first->arrival_time <<
					" with " << first->num_items <<
					" items, took " <<
					(timeUnits - first->arrival_time) <<
					" units" << endl;
					lines[i].dequeue();
				}
			}
		}
		// Adds shopper if timeUnits matches arrival_time
		if (!allShoppers.isEmpty())
		{
			Shopper *next = allShoppers.front();
			if (next->arrival_time == timeUnits)
			{
			lines[fastestLine(next->num_items)].enqueue(*next);
			allShoppers.dequeue();
			}
		}
		timeUnits++;
	}
}

// Returns false when all shoppers are done
bool GrocerySim::continueSim()
{
	if (!allShoppers.isEmpty())
		return true;
	for (int i = 0; i < (numLines+numExpLines); i++)
	{
		if (!lines[i].isEmpty())
			return true;
	}
	return false;
}

// Returns the fastest line that a shopper with a specified number of items can
// enter.
int GrocerySim::fastestLine(int items)
{
	int bestLine;
	if (items > maxExpItems)
		bestLine = numExpLines;
	else
		bestLine = 0;

	int minItems = lines[bestLine].totalItems();

	for (int i = (bestLine+1); i < (numExpLines+numLines); i++)
	{
		if (lines[i].totalItems() < minItems)
		{
			bestLine = i;
			minItems = lines[i].totalItems();
		}
	}
	return bestLine;
}
