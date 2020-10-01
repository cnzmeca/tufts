/*
Christian Zinck
HW3
9/30/17
*/
#ifndef GROCERYSIM_H
#define GROCERYSIM_H

#include <fstream>
#include <iostream>

#include "CheckoutQueue.h"
#include "shopper.h"

using namespace std;

class GrocerySim
{
public:
	GrocerySim(int a, int b, int c);
	~GrocerySim();

	void run(istream &infile);
private:
	CheckoutQueue *lines;
	CheckoutQueue allShoppers;

	int numLines;
	int numExpLines;
	int maxExpItems;

	bool continueSim();
	int fastestLine(int items);
};

#endif
