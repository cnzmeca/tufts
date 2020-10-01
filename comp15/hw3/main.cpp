/*
Christian Zinck
HW3
9/30/17
*/
#include <iostream>
#include <fstream>
#include <cstdio>

#include "GrocerySim.h"
#include "CheckoutQueue.h"
#include "shopper.h"

using namespace std;
int main(int argc, char *argv[])
{
	// Checks for valid number of args
	if (argc < 4)
	{
		cerr << "Invalid number of arguments." << endl;
		return 1;
	}

	// Reformats args in argv
	int a = 0;
	int b = 0;
	int c = 0;
	
	sscanf (argv[1], "%d", &a);
	sscanf (argv[2], "%d", &b);
	sscanf (argv[3], "%d", &c);

	// Simulation object
	GrocerySim sim(a, b, c);

	// Runs sim with file
	if (argc == 5)
	{
		ifstream infile;
		string filename = argv[4];
		
		infile.open(filename);
		if (!infile.is_open())
		{
			cerr << "Failed to open file" << endl;
			return 1;
		}
		sim.run(infile);
		infile.close();
	}

	// Runs sim with cin
	else
		sim.run(cin);

		
}
