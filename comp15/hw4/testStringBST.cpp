/*
Christian Zinck
10/27/17
HW 4
Testfile for StringBST Class
*/

#include "StringBST.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
	//
	string strs[] = {"Ram", "Horse", "Horse", "Swan", "Swan", "Swan",
	"Deer", "Deer", "Deer", "Deer", "Kingfisher", "Bison", "Llama",
	"Llama"};	

	// Trees
	StringBST t1 = StringBST();
	StringBST t2 = StringBST(strs, 14);
	
	// Value tests
	cout << t1.isEmpty() << endl; //1
	cout << (t2.size()) << endl; //14	
	cout << (t2.getMin()) << endl; //Bison
	cout << (t2.getMax()) << endl; //Swan
	cout << (t2.contains("Deer")) << endl; //1
	cout << (t2.contains("Pig")) << endl; //0

	// Modifier tests
	t1.add("Cow"); //Empty
	t1.print();
	t2.add("Ram"); //Already in tree
	t2.print();
	t2.add("Elephant"); //Not in tree
	t2.print();

	t1.remove("Cow"); //Remove root
	t1.print();
	t2.remove("Horse"); //Remove duplicate
	t2.print();
	t2.remove("Bison"); //Remove leaf
        t2.print();
	t2.remove("Kingfisher"); //Remove node with 1 child
        t2.print();
	t2.remove("Horse"); //Remove node with 2 children
        t2.print();

	t2.clear();
	t2.print();
}
