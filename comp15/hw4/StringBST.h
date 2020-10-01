/*
Christian Zinck
10/27/17
HW 4
Definition of StringBST Class
*/

#ifndef STRINGBST_H
#define STRINGBST_H

#include <iostream>
#include <string>

using namespace std;

class StringBST
{
	public:
		StringBST();
		StringBST(string arr[], int size);
		~StringBST();
		
		bool isEmpty();
		void clear();
		int size();
		void print();
		void add(string word);
		bool remove(string word);
		string getMin();
		string getMax();
		void removeMin();
		void removeMax();
		bool contains(string word);

	private:
		struct BSTNode {
			string value;
			BSTNode *left;
			BSTNode *right;
			int count;
		};

		BSTNode *root;
	
		void clearHelp(BSTNode *start);	
		int sizeHelp(BSTNode *start);
		string printHelp(BSTNode *start);
		BSTNode* addHelp(BSTNode *start, string word);
		BSTNode* removeHelp(BSTNode *start, string word, bool &success);
		BSTNode* getMinHelp(BSTNode *start);
		BSTNode* getMaxHelp(BSTNode *start);
		bool containsHelp(BSTNode *start, string word);
};

#endif

