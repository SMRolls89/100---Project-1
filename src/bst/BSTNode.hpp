/**
 * Name: Steffe Reyes (A16083679)
 * Ji Hyun An (A91108783)
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BSTNode {

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    Data data;

    /**Initializing a BSTNode with given data/ no parent and no children*/ 
    BSTNode(const Data& d) : data(d) {
    	left = right = parent = 0;
    }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() { return data; }

    /**Return the successor of a BSTNode, or 0 if none */
    BSTNode<Data>* successor() {
	 BSTNode<Data> *curr = this;
	  
	  //if there's a right subtree, then successor
	  //is the most left node of the right subtree
	 /** if(curr->right) {
		  curr = curr->right;
		  
		  while (curr->left) {
			  curr = curr->left;
		  }
		  return curr;
	  }
	  //if successor is parent
	  else {
		 while (curr->parent) {
			if (curr->left == this) {
			       return curr->parent;
			}
	 		if (curr->parent && curr->data > this->data) {
				return curr->parent;
			}
		}		
	    
	  } 
	  //otherwise, no successor found
	    return 0;
    }*/
	    if (this->right == 0) {

		    if (this->parent == 0){
			    return 0;
		    }

		    if (this == ((this->parent) -> left)) {
			    return this->parent;
		    }
		    else {
			   while(curr != (curr->parent) -> left) {
				  curr = curr->parent;
				 if(curr->parent == 0)
					return 0;
			   }
			   curr = curr->parent;
			   return curr;
		    }
	    }

	    else {
		    curr = this->right;

		    while (curr->left != 0){
			    curr = curr->left;
		    }

		    return curr;
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
