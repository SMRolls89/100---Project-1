/**
 * Steffe Reyes (A16083679)
 * Ji Hyun An (A91108783)
 */
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {}

    /** delete every node in the BST */
    ~BST() {
	    deleteAll(root);
    }

    /** insert a Node  */
    bool insert(const Data& item) {
	    //if root is empty, add new node to root
	    if (empty()) {
		    root = new BSTNode<Data> (item);

		    ++isize;
		    return true;
	    }
	    //root node not empty, so insert node to correct position
	    else {
		    BSTNode<Data>* curr = this->root;

		    while(curr) {
			    //if node belongs in left subtree
			    if(item < curr->data) {
				    if(curr->left == 0) {
					    curr->left = new BSTNode<Data> (item);
					    (curr->left)->parent = curr;
					    break;
				    }
				    else {
					    //go to the next left leaf
					    curr = curr->left;
				    }
			    }

			    }
			    //node belongs in the right subtree
			    else if (curr->data < item) {
				    if (curr->right == 0) {
					    curr->right = new BSTNode<Data> (item);
					    (curr->right)->parent = curr;
					    break;
				    }
				    else {
					    //go to next right leaf
					    curr = curr->right;
				    }
			    }

			    //if item is a duplicate
			    else {
				    //if it is equal to curr
				    if (!(item < curr->data) && !(curr->data < item)) {
					    return false;
				    }
			    }
		    }

		    ++isize;

		    return true;
	   
    }

    /** TODO */
    iterator find(const Data& item) const {
	  BSTNode<Data>* curr = this->root;
	  
	  //if BST is empty
	  if (empty()) {
		  return 0;
	  }

	  //if BST not empty, search for item
	  while(curr) {
		  if (item < curr->data) {
			  curr = curr->left;
		  }
		  else if (curr->data < item) {
			  curr = curr->right;
		  }
		  else { //found a match!
			  return curr;
		  }
	  }

	  //if item not found, or pointing past last node
	  return this -> end();

    }

    /** TODO */
    bool deleteNode(const Data& item) { return false; }

    /** return number of items currently in BST */
    unsigned int size() const { 
	    return isize;
    }

    /** calculates the height of the BST */
    int height() const {
	    BSTNode<Data>* curr = this->root;
	    //empty BST
	    if (isize == 0){
		return -1;
	    }
	    //if only root node (one node)
	    else if (isize == 1) {
		return 0;
	    }	
    	    else { //height is not -1 or 0, call height helper method
		return heightHelper(curr);
	    }		
    }

    /** checks if BST is empty or not */
    bool empty() const { 
	    if (root == 0) { 
		    return true;
	    }
	    else { //BST not empty
		    return false;
	    }
    }

    /** return an iterator pointing to the first item in BST */
    iterator begin() const { 
	    return BST<Data>::iterator(first(root)); 
    }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /**perform an inorder traversal of BST */
    vector<Data> inorder() const {

   	    return inroder(root); 
    }

    /**
     * DO NOT CHANGE THIS METHOD
     * Prints a tree, including its structure to an
     * output stream to help with grading and debugging.
     */
    void print(ostream* out) {
        if (empty()) {
            *out << "(Empty tree)" << endl;
            return;
        }

        // Using a queue to traverse a tree is otherwise
        // known as a breadth first traversal of the tree.
        // It's useful here to show which nodes are on which
        // level.
        queue<BSTNode<Data>*> toVisit;
        toVisit.push(root);
        int nodesPerLevel = 1;
        int totalSpacing = 1 << iheight;

        for (int i = 0; i <= iheight; i++) {
            for (int j = 0; j < nodesPerLevel; j++) {
                BSTNode<Data>* curr = toVisit.front();
                toVisit.pop();
                if (curr == nullptr) {
                    *out << "X";
                    // If we have an entire missing subtree, we
                    // would like to print X's in place of all
                    // nodes because it avoids ambiguity
                    toVisit.push(nullptr);
                    toVisit.push(nullptr);
                } else {
                    *out << curr->getData();
                    toVisit.push(curr->left);
                    toVisit.push(curr->right);
                }
                for (int k = 0; k < totalSpacing / nodesPerLevel; k++) {
                    *out << "\t";
                }
            }
            *out << endl;
            nodesPerLevel *= 2;
        }
    }

  private:
    /** Helper function for begin() */
    /** Find the first element of the BST */
    static BSTNode<Data>* first(BSTNode<Data>* root) { 
	    if(root == 0) {
		    return 0;
	    }
	    while (root->left !=0) {
		    root = root->left;
	    }
	    return root;
    }


    /** delete all nodes */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
	    if (n == 0){
		    return;
	    }

	    delete(n->left);
	    delete(n->right);
	    delete n;
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
    // recursive height helper function
    int heightHelper(BSTNode<Data>* n) const {

	    int right = heightHelper(n->right)
	    int left = heightHelper(n->left)

	    if (left < right){
		    return (right+1);
	    }
	    else {
		    return (left+1);
	    }
    }

    //Recursive inroder traversal helper function 
    vector<Data> inorder(BSTNode<Data>* n) const {
	    vector<Data> v1;

	    if (n == 0) {
		    return v1; //can you return an empty vector?
	    }
	    //traverse the left subtree
	    inorder(n->left);
	    //add current node to vector
	    v1.push_back(*n);
	    //traverse the right subtree
	    inorder(n->right);

	    return v1;
    }
};

#endif  // BST_HPP
