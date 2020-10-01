/*
Christian Zinck
10/27/17
HW 4
Implementation of StringBST Class
*/

#include "StringBST.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Default constructor
StringBST::StringBST() {
	root = NULL;
}

// Array constructor
StringBST::StringBST(string arr[], int size) {
	root = NULL;
	for (int i = 0; i < size; i++)
		add(arr[i]);
}

// Destructor
StringBST::~StringBST() {
	clearHelp(root);
	delete root;
}

// Returns true if tree is empty
bool StringBST::isEmpty() {
	return root == NULL;
}

// Clears tree
void StringBST::clear() {
	clearHelp(root);
	root = NULL;
}

// Returns the size of the tree
int StringBST::size() {
	return sizeHelp(root);
}

// Prints the tree in correct format
void StringBST::print() {
	cout << printHelp(root) << endl;
}

// Adds a string word to the tree
void StringBST::add(string word) {
	root = addHelp(root, word);
}

// Removes a string word from the tree and returns a bool if successful
bool StringBST::remove(string word) {
	bool success = false;
	root = removeHelp(root, word, success);
	return success;
}

// Returns the string value of the minimum tree element
string StringBST::getMin() {
	if (isEmpty())
		throw runtime_error("empty_tree");
	return (getMinHelp(root)->value);
}

// Returns the string value of the maximum tree element
string StringBST::getMax() {
	if (isEmpty())
		throw runtime_error("empty_tree");
	return (getMaxHelp(root)->value);
}

// Removes the minimum tree element
void StringBST::removeMin() {
	remove(getMin());
}

// Removes the maxiumum tree element
void StringBST::removeMax() {
	remove(getMax());
}

// Returns true if the string word is an element in the tree
bool StringBST::contains(string word) {
	return containsHelp(root, word);
}

// Helps clear the tree. Takes a BSTNode pointer
void StringBST::clearHelp(BSTNode *start){
	if (start != NULL)
	{
		clearHelp(start->left);
		clearHelp(start->right);
		delete start;
	}
}

// Helps determine tree size. Takes a BSTNode pointer
int StringBST::sizeHelp(BSTNode *start) {
	if (start == NULL)
		return 0;
	return (start->count + sizeHelp(start->left) + sizeHelp(start->right));
}

// Helps print tree. Takes a BSTNode pointer
string StringBST::printHelp(BSTNode *start) {
	if (start == NULL)
		return "[]";
	else
	{
		stringstream ss;
		string s;
		ss << (start->count);
		ss >> s;
		return "[" + (printHelp(start->left)) + " " + (start->value) + 
		" " + s + " " + (printHelp(start->right)) + "]";
	}
}

// Helps add string word to tree. Takes and returns a BSTNode pointer
StringBST::BSTNode* StringBST::addHelp(BSTNode *start, string word) {
	if (start == NULL){
		start = new BSTNode;
		start->value = word;
		start->count = 1;
		start->left = NULL;
		start->right = NULL;
	}
	else if (start->value == word)
		start->count++;
	else if (start->value > word)
		start->left = addHelp(start->left, word);
	else if (start->value < word)
		start->right = addHelp(start->right, word);
	return start;
}

// Helps remove string word from tree. Takes and returns a BSTNode pointer.
// Also takes a reference to a bool in order to return success
StringBST::BSTNode* StringBST::removeHelp(BSTNode *start, string word,
					 bool &success) {
	if (start == NULL)
		return NULL;
	else if (start->value > word)
                start->left = removeHelp(start->left, word, success);
        else if (start->value < word)
                start->right = removeHelp(start->right, word, success);
	else if (start->value == word)
	{
		success = true;
		if (start->count != 1)
                	start->count--;
		else if (start->left != NULL && start->right != NULL)
		{
			BSTNode* sub = getMaxHelp(start->left);
			start->value = sub->value;
			start->count = sub->count;
			bool temp = false;
			for (int i = 0; i < start->count; i++)
				removeHelp(start->left, start->value, temp);
		}
		else if (start->left != NULL || start->right != NULL)
		{
			BSTNode* rm = start;
			if (start->left == NULL)
				start = start->right;
			else if(start->right == NULL)
				start = start->left;
			delete rm;
		}
		else
		{
			delete start;
			start = NULL;
		}
	}
	return start;
}

// Helps get min value. Takes and returns a BSTNode pointer
StringBST::BSTNode* StringBST::getMinHelp(BSTNode *start) {
	if (start->left == NULL)
		return start;
	else
		return getMinHelp(start->left);
}

// Helps get max value. Takes and returns a BSTNode pointer
StringBST::BSTNode* StringBST::getMaxHelp(BSTNode *start) {
	if (start->right == NULL)
		return start;
	else
		return getMaxHelp(start->right);
}

// Helps determine if string word is in tree. Takes a BSTNode pointer. 
// Returns true if word is in tree
bool StringBST::containsHelp(BSTNode *start, string word) {
	if (start == NULL)
		return false;
	else if (start->value == word)
		return true;
	else if (start->value > word)
		return containsHelp(start->left, word);
	else if (start->value < word)
		return containsHelp(start->right, word);
}	
