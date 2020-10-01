/*
 *
 *  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
 *
 *  CharSequence.h
 *  Complete SequenceA Class Header and Declaration
 *  Modified By (UTLN): czinck01
 *           On       : 9/15/17
 *
 */

#ifndef CHARSEQUENCE_H
#define CHARSEQUENCE_H

class CharSequence
{
public:
	CharSequence();
	CharSequence(char letter);
	CharSequence(char arr[], int size);
	~CharSequence();
	
	bool isEmpty();
	void clear();
	int size();
	char first();
	char last();
	char elementAt(int index);
	void print();
	void pushAtBack(char letter);
	void pushAtFront(char letter);
	void insertAt(char letter, int index);
	void insertInOrder(char letter);
	void popFromFront();
	void popFromBack();
	void removeAt(int index);
	void replaceAt(char letter, int index);
	void concatenate(CharSequence *ptr);
	void shrink();
	
private:
	int count;
	int capacity;
	char *sequence;
	
	void resize(int newCapacity);
	void expand();
	void shiftUp(int index);
	void shiftDown(int index);
};

#endif
