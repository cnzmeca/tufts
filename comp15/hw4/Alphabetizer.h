/*
Christian Zinck
10/27/17
HW 4
Definition of Alphabetizer Class
*/

#ifndef ALPHABETIZER_H
#define ALPHABETIZER_H

#include "StringBST.h"

#include <iostream>
#include <fstream>

using namespace std;

class Alphabetizer {
	public:
		Alphabetizer();
		~Alphabetizer();

		void run();
		void run(string filename, string order);
	private:
		void print(string source, string order);

		StringBST tree;
};

#endif
