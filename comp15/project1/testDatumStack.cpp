/*
Christian Zinck
10/13/17
Project 1
Test file for DatumStack class
*/
#include <iostream>

#include "DatumStack.h"
#include "Datum.h"
using namespace std;

int main()
{
	Datum d1 = Datum(1);
	Datum d2 = Datum(2);
	Datum d3 = Datum(3);

	Datum data[3] = {d1, d2, d3};

	DatumStack s1 = DatumStack();
	DatumStack s2 = DatumStack(data, 3);
	
	cout << (s2.size() == 3) << endl; //1
	cout << (s2.top() == d3) << endl; //1
	cout << (s1.isEmpty()) << endl; //1

	s1.push(d2);
	s1.print(); //2
	s1.pop();
	s1.print(); //Empty

	s2.push(d1);
	s2.print(); //1 2 3 1
	s2.pop();
	s2.print(); //1 2 3
	s2.clear();
	s2.print(); //Empty

	s2.top(); //Empty stack error
	s2.pop(); //Empty stack error
}
