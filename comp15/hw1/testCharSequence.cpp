/*
 *
 *  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
 *
 *  testCharSequence.cpp
 *  Testing File for your sequence CharSequence class
 *
 *  Written by:
 *        UTLN:
 *          on:
 */

#include <iostream>
#include "CharSequence.h"

using namespace std;

int main()
{
	// Tests each constructor
	CharSequence seq1 = CharSequence();
	CharSequence seq2 = CharSequence('a');
	char arr[3] = {'b', 'c', 'd'};
	CharSequence seq3 = CharSequence(arr, 3);
	
	CharSequence *ptr2;
	ptr2 = &seq2;
		
	// All should return 1
	cout << seq1.isEmpty() << endl;
	cout << !seq2.isEmpty() << endl;
	cout << (seq3.size() == 3) << endl;
	cout << (seq3.first() == 'b') << endl;
	cout << (seq3.last() == 'd') << endl;
	cout << (seq3.elementAt(1) == 'c') << endl;
	
	// Sequence Changers
	seq3.pushAtBack('e');
	seq3.print(); //Should be 'bcde'
	seq3.pushAtFront('a');
	seq3.print(); //Should be 'abcde'
	seq3.insertAt('f', 5);
	seq3.print(); //Should be 'abcdef'
	seq3.insertInOrder('g');
	seq3.print(); //Should be 'abcdefg'
	seq3.popFromFront();
	seq3.print(); //Should be 'bcdefg'
	seq3.popFromBack();
	seq3.print(); //Should be 'bcdef'
	seq3.removeAt(4);
	seq3.print(); //Should be 'bcde'
	seq3.replaceAt('a',0);
	seq3.print(); //Should be 'acde'
	seq3.concatenate(ptr2);
	seq3.print(); //Should be 'acdea'
	seq3.clear();
	seq3.print(); //Should be ''
	
	// Exceptions (checked one at a time)
	seq1.replaceAt('e',1);	
}
