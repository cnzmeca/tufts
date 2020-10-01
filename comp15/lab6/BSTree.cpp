#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>

#include "BSTree.h"

using namespace std;

//
// A couple handy functions for creating new, initialized nodes.
// We could make constructors for the struct, but let's keep things
// simple. 
//

//
// Return a pointer to a newly allocated leaf node with value v.
//
BST::BSTNode *BST::newBSTNode(int v)
{
        BST::BSTNode *newNode = new BST::BSTNode;

        newNode->value = v;
        newNode->left  = NULL;
        newNode->right = NULL;
 
       return newNode;
}

//
// Return a pointer to a newly allocated node initialized with given
// values. 
//
BST::BSTNode *BST::newBSTNode(int v, BSTNode *left, BSTNode *right)
{
        BST::BSTNode *newNode = newBSTNode(v);

        newNode->left  = left;
        newNode->right = right;
 
       return newNode;
        
}

//
// Initialize an empty tree.
//
BST::BST()
{
	root = NULL;	
}

//
// Delete all the nodes in the tree
//
BST::~BST()
{
	postOrderDelete();
}

//
// Insert: public version of Insert takes a value only and
// 	   inserts in the tree at the root
//
void BST::unbalancedInsert(int v)
{
	root = unbalancedInsert(root, v);
}

//
// Insert: (private version) inserts a value in the tree rooted at r
//
//   Return the current tree WITH the value inserted
//
//   note: ALWAYS adds a leaf.  
//
//   Implementation note:
//       When the base case is reached, we are inserting the value
//       into an empty tree, i. e., r is NULL.
//       In this case, we create a new leaft node with the given data
//       value and return a pointer to that.  If the caller had a
//       non-empty tree node, then they will set the corresponding
//       subtree in their node to the result.
//       DRAW THIS OUT!
//
BST::BSTNode *BST::unbalancedInsert(BSTNode *r, int v)
{
	if (r == NULL) {
                return newBSTNode(v);
	} else if (v < r->value) {
		r->left = unbalancedInsert(r->left, v);
		return r;

	} else {
		r->right = unbalancedInsert(r->right, v);
		return r;
	}
}


//****************** inorder *****************//

//
// Perform an in-order print starting at the root of the entire tree
//
void BST::inOrder()
{
	inOrder(root);		// calls the next one
}

//
// Perform an in-order print of the subtree rooted at the given node
//
void BST::inOrder(BSTNode *root)
{
	if (root->left != NULL)
		inOrder(root->left);
	cout << (root->value) << " ";
	if (root->right != NULL)
		inOrder(root->right);
}


//****************** postorder *****************//

//
// Perform post-order traversal to delete the entire tree
//
void BST::postOrderDelete()
{	
	postOrderDelete(root);
}

//
// Perform post-order traversal to delete tree rooted at give node
// Question to ponder:  Could we use another traversal to delete the
//                      tree?
//
void BST::postOrderDelete(BSTNode *root)
{
	if (root->left != NULL)
                postOrderDelete(root->left);
        if (root->right != NULL)
                postOrderDelete(root->right);
	delete [] root;

}


//****************** preorder *****************//

//
// Perform a pre-order print of the entire tree.
// Question to ponder:  Can we do this without a helper function?
//
void BST::preOrder()
{
	preOrder(root);		// calls the next function (really needed?)
}

//
// Perform a pre-order print of the subtree rooted at given node.
// Uses a stack from the STL rather than the C++ run time stack.
//
void BST::preOrder(BSTNode *root)
{
	//preorder with a stack
	stack<BSTNode*> s;
	s.push(root);

        while (s.size() != 0)
        {
                BSTNode *temp = s.top();
		cout << (temp->value) << " ";
		s.pop();
		if (temp->right != NULL)
			s.push(temp->right);
		if (temp->left != NULL)
			s.push(temp->left);
        }

}


//****************** levelorder *****************//
//
// Perform a level-order print of the entire tree
//
void BST::levelOrder()
{
	levelOrder(root);
}

//
// Perform a level-order print of the subtree rooted at the given node
// Uses a queue from the STL
//
void BST::levelOrder(BSTNode *root)
{
	queue<BSTNode*> q;
        q.push(root);

        while (q.size() != 0)
        {
                BSTNode *temp = q.front();
                cout << (temp->value) << " ";
                q.pop();
                if (temp->left != NULL)
                        q.push(temp->left);
                if (temp->right != NULL)
                        q.push(temp->right);
        }
	
}
