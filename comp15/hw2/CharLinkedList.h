
/*
 *
 *  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in hur
 *
 *  CharLinkedList.cpp
 *  Complete CharLinkedList Class Header and Declaration
 *  Modified By (UTLN): czinck01
 *           On       :	9/22/17
 *
 */ 

#ifndef CHARLINKEDLIST_H
#define CHARLINKEDLIST_H

class CharLinkedList
{
public:
        CharLinkedList();
        CharLinkedList(char letter);
        CharLinkedList(char arr[], int size);
        ~CharLinkedList();

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
        void concatenate(CharLinkedList *secondList);
        void shrink();
	bool find(char letter);

private:

	struct CharNode{
		char element;
		CharNode *prev;
		CharNode *next;
	};

	CharNode *front;
	CharNode *back;
	
	CharNode *newCharNode(char letter);
	void insertIntoEmpty(char letter);
};

#endif
