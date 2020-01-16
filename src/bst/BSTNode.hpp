/**
 * Name: Steffe Reyes (A16083679)
 * Ji Hyun An (A91108783)
 * CSE100 PA1
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * This class contains the constructor that initializes an empty BST
 * and the successor method that finds the successor of a BSTNode
 * 
 */
template <typename Data>
class BSTNode {

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    Data data;

    /**Initialize a BSTNode with given the given data having no parent and no children
    * aka initialize the root node 
    */
    BSTNode(const Data& d) : data(d) {
    	left = right = parent = 0;
    }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() { return data; }

    /**Return the successor of a BSTNode, or 0 if none
     * The successor of a BSTNode is the node with the smallest element
     * that is greater than the BSTNode
     */
    BSTNode<Data>* successor() {
	BSTNode<Data> *curr = this;
	 
	//if node does not have a right child, then successor must be one of its ancestors	 
	if (curr->right == 0) {
		
		//if node is the root, with no right child, therefore no successor
	 	if (curr->parent == 0){
		 	return 0;
	 	}
		
		//if  node has a parent and current node is the left child 
		//then successor is simply its parent
	 	if (curr == ((curr->parent) -> left)) {
		 	return curr->parent;
	 	}
		//otherwise successor is one of its ancestors
	 	else {
		 	while(curr != (curr->parent) -> left) {

			 	curr = curr->parent;
	
				//this is when the Node is the largest in BST, hence no successor	
				if(curr->parent == 0) {
				 	return 0;
				}
	 	 	}
		
		curr = curr->parent;
		return curr;
	 	}
	}
    	
	//if Node has a right child
	else {	
		//go to the right node
	 	curr = curr->right;
		
		//if current node has a left node, keep going to the leftmost node
		//otherwise successor will be the right child
		while (curr->left != 0) {
			 curr = curr->left;
		}
	
		return curr;
	 }
     }
};

/**
 * DO NOT CHANGE THIS METHOD
 * Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
