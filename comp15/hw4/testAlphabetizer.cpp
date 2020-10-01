/*
Christian Zinck
10/27/17
HW 4
Testfile for Alphabetizer Class
*/

#include "StringBST.h"
#include "Alphabetizer.h"

#include <iostream>

using namespace std;

int main() {
	Alphabetizer a = Alphabetizer();
	a.run();
	a.run("test.txt", "f");
}
