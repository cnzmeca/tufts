/*
 *
 *  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in hur
 *
 *  testCharLinkedList.cpp
 *  Testing File for your sequence CharLinkedList class
 *
 *  Written by: Christian Zinck
 *        UTLN: czinck01
 *          on: 9/22/17
 */

#include <iostream>
#include "CharLinkedList.h"

using namespace std;
int main()
{
	// Tests constructors
	CharLinkedList list1 = CharLinkedList();
	CharLinkedList list2 = CharLinkedList('z');
	char arr[3] = {'a', 'b', 'c'};
	CharLinkedList list3 = CharLinkedList(arr, 3);
	
	// Test booleans (all should print true/1)
	cout << (list1.isEmpty());
	cout << (!list2.isEmpty());

	cout << (list1.size()==0);
	cout << (list2.size()==1);

	cout << (list3.first()=='a');
	cout << (list3.last()=='c'); 
	
	cout << (list3.elementAt(1)=='b');
	cout << (list2.find('z')) << endl;

	// Tests modifiers
	list3.pushAtFront('d');
	list3.print(); //dabc
	list3.pushAtBack('f');
	list3.print(); //dabcf
	list3.insertAt('g',2);
	list3.print(); //dagbcf
	list3.insertInOrder('f');
	list3.print(); //dafgbcf
	list3.popFromFront();
	list3.print(); //afgbcf
	list3.popFromBack();
	list3.print(); //afgbc
	list3.removeAt(1);
	list3.print(); //agbc
	list3.replaceAt('d',1);
	list3.print(); //adbc
	list3.concatenate(&list2);
	list3.print(); //adbcz	
	list3.clear();
	list3.print(); //

	list1.replaceAt('a',2);
}
