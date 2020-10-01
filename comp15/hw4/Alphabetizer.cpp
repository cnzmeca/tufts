/*
Christian Zinck
10/27/17
HW 4
Implementation of Alphabetizer Class
*/

#include "StringBST.h"
#include "Alphabetizer.h"

#include <iostream>
#include <fstream>

using namespace std;

// Default constructor
Alphabetizer::Alphabetizer() {
	tree = StringBST();
}

// Destructor
Alphabetizer::~Alphabetizer() {
}

// Alphabetizes a list of words from cin and prints in correct order
void Alphabetizer::run() {
	string order;
	cin >> order;

	string word;
	for (cin >> word; (!cin.eof()); cin >> word)
		tree.add(word);
	print("cin", order);
}

// Alphabetizes a list of words from filename and prints in correct order
void Alphabetizer::run(string filename, string order) {
	ifstream infile;
	infile.open(filename);
	if (!infile.is_open())
	{
		cerr << "Failed to open file." << endl;
		return;
	}
	string word;
	for (infile >> word; (!infile.eof()); infile >> word)
		tree.add(word);
	infile.close();

	print(filename, order);
}

// Prints list in correct format. Takes 2 strings: a source and an order
void Alphabetizer::print(string source, string order)
{
	cout << ("[ " + source + ", " + order + " : ");
	if (order == "f")
	{
		while (!tree.isEmpty())
		{
			cout << tree.getMin();
			tree.removeMin();
			if(!tree.isEmpty())
				cout << ", ";
		}
	}
	else
	{
		while (!tree.isEmpty())
                {
                        cout << tree.getMax();
                        tree.removeMax();
                        if(!tree.isEmpty())
                                cout << ", ";
                }
	}
	cout << " ]" << endl;
}
