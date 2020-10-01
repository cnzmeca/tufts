/*
Christian Zinck
10/27/17
HW 4
Main file for HW4
*/

#include "StringBST.h"
#include "Alphabetizer.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	Alphabetizer a = Alphabetizer();
	if (argc == 3)
	{
		string order = argv[1];
		string filename = argv[2];
		if (order == "f" || order == "r")
			a.run(filename, order);
		else
			cerr << "Usage:  alphabetizer [order filename]" << endl;
	}
	else if (argc == 1)
		a.run();
	else
		cerr << "Usage:  alphabetizer [order filename]" << endl;
}
