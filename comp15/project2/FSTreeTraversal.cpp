/*
Christian Zinck
Project 2
11/17/17
Traverses a tree and prints all file paths
*/

#include <iostream>

#include "FSTree.h"
#include "DirNode.h"

using namespace std;

void printDir(DirNode *root);

int main(int argc, char *argv[]) {
	string rootName(argv[argc-1]);
	
	// Creates FStree and calls printDir on it
	FSTree tree = FSTree(rootName);	
	DirNode *root = tree.getRoot();
	printDir(root);
}

// Helper function that recurses through FS by calling on root Dir
void printDir(DirNode *root) {
	// Prints all files in current Dir
	for (int i = 0; i < root->numFiles(); i++)
		cout << root->getName() << "/" << root->getFile(i) << endl;
	// Calls printDir for all subDirs
	for (int i = 0; i < root->numSubDirs(); i++)
	{
		string temp = root->getSubDir(i)->getName();
		root->getSubDir(i)->setName(root->getName() + "/" + temp);
		printDir(root->getSubDir(i));
	}
}
