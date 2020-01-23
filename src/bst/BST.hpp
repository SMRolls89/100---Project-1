/**
 * Steffe Reyes (A16083679)
 * Ji Hyun An (A91108783)
 * CSE100 - PA1
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
 * This file contains the definition of a BST.
 * Most of the BST functions are implemented here
 * such as insert, delete, find, etc.
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

    vector<Data> v1;

  public:

    //BSTNode<Data>* root;
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {

	    vector<Data> v = inorder();
	    int depth = -1; //what is depth exactly?

	    root = buildSubtree(v, 0, v.size() -1, depth);
	    //bst = buildSubtree(v, 0, v.size() -1, depth); 
    }

    /** Delete every node in the BST
     * Implemented by the DeleteAll helper function
     */
    ~BST() {
	    deleteAll(root);
    }

    /** Insert a node with the given data  */
    bool insert(const Data& item) {
	    //if root is empty, add a node (root)
	    if (empty()) {
		    root = new BSTNode<Data> (item);
		    
		    //update the size of the BST and return true
		    ++isize;
		    return true;
	    }
	    //if root node not empty, insert node to correct position
	    else {
		    BSTNode<Data>* curr = this->root;

		    while(curr) {
			    /** If element to be inserted is smaller than the current node element
			    * then element belongs in the left subtree
			    */
			    if(item < curr->data) { 
				    // if the left child is empty, then insert new element to the left child
				    if(curr->left == 0) {
					    curr->left = new BSTNode<Data> (item);
					    (curr->left)->parent = curr;
					    break;
				    }
 				    else {
					    //otherwise go to the next left leaf
					    curr = curr->left;
				    }
			    }
			    /**If element to be inserted is greater than the current node element
			     * then element belongs in the right subtree
			     */
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

			    /* otherwise, element to be inserted must be equal to the current element
			     * hence a duplicate
			     * return false
			     */
			    else {
				    //check to make sure they are indeed equal
				    if (!(item < curr->data) && !(curr->data < item)) { 
					    return false;
				    }
			    }
		    }
	    }

	    	    //lines below will only be executed when a new node is inserted
		    ++isize;
		    return true;
	   
    }

    /** Find an item in the BST 
     * This method will return an iterator pointing to the item 
     * we are trying to find.
     * Or it will return an iterator pointing past the last node
     * of the BST if the item was not found.
     */
    iterator find(const Data& item) const {
	  BSTNode<Data>* curr = root;
	  
	  //if BST is empty
	  if (empty()) {
		  return 0;
	  }

	  //if BST not empty, search for item
	  while(curr) {
		  //If item is smaller than the current element, go the left leaf
		  if (item < curr->data) {
			  curr = curr->left;
		  }
		  //If item is larger than the current element, go to the right leaf
		  else if (curr->data < item) {
			  curr = curr->right;
		  }
		  else { //found a match!
			  return curr;
		  }
	  }

	  //otherwise, item not found
	  return this->end(); //got rid of this->


    }

    /** TODO */
    bool deleteNode(const Data& item) {
	    	   
	   BSTNode<Data>* n = root; 
	    //base case: empty bst
	    if ( n == NULL ) return false;
	    
	    //find if Node to be deleted is in BST
	    while (n) {
		    if (item < n->data){
			    n = n->left;
		    }
		    else if (n->data < item){
			    n = n->right;
		    }
		    //found it!!
		    else { 
			    //CASE 1: node to be deleted has no children
			    // it is a leaf node
			    if (n->left == NULL && n->right == NULL) {
				    if ( n != root ){
					    //either it is a left child or right child
					    if ( (n->parent)->left == n )
						    (n->parent)->left = nullptr;
					    else
						    (n->parent)->right = nullptr;
				    }

				    //if BST only has one  node, the root, delete it
				    else
					    root = nullptr;

				    delete n; //free it!
				    --isize; //update size
			    }

			    //CASE 2:  node to be deleted has two  children
			    else if (n->left && n->right) {

				    //find it's successor node
				    BSTNode<Data>* succ = minKey(n->right);

				    //store the successor value
				    Data temp = succ->data;

				    //recursively delete the successor
				    deleteNode(succ->data);

				    //copy the value of successor to the current node
				    n->data = temp;
			    }

			    //CASE 3: node to be deleted has only one child
			    else {	

				    //find the child node
				    BSTNode<Data>* child; 
				    if(n->left){
				    	child = n->left;
				    }
				    else{
					 child = n->right;
				    }
	
				    //if node to be deleted is not a root node
				    //then set it's parent to it's child
				    if (n != root) {
					    if (n == (n->parent)->left)
						    (n->parent)->left = child;
					    else
						    (n->parent)->right = child;
				    }

				    //if node to be deleted is root node, then set root to child
				    else
					    root = child;

				    delete n;
				    --isize;
			    }

			    return true;

		    }
	    }
	    return false;
    }

    /** return number of items currently in BST */
    unsigned int size() const { 
	    return isize;
    }

    /** calculates the height of the BST */
    int height() const {
	    
	    //if empty BST
	    if (root == 0 ) { 
		return -1;
	    }
	    //if there's only the root node (one node)
	    else if (root->right == 0 && root->left == 0) {
		return 0;
	    }	
    	    else { //if more than 1 node, hence height is not -1 or 0, call height helper method
		return heightHelper(root);
	    }		
    }

    /** checks if BST is empty or not */
    bool empty() const { 
	    if (isize ==  0) { 
		    return true;
	    }
	    else { //BST not empty
		    return false;
	    }
    }

    /** Return an iterator pointing to the first item in the BST
     * Implemented through the use a helper function
    */
    iterator begin() const { 
	    return BST<Data>::iterator(first(root)); 
    }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** Perform an inorder traversal of BST 
     * and store its elements into a vector.
     * Implemeneted by the use of a halper function.
    */
    vector<Data> inorder() {

   	    return inorder(root); 
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
	    //check if BST is empty 
	    if(root == 0) {
		    return 0;
	    }
	    //go the the left most node
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
	    //if BST is empty, nothing to delete
	    if (n == 0){
		    return;
	    }
	    //deleting every member of the Node recursively
	    deleteAll(n->left);
	    deleteAll(n->right); 
	    delete n;
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end, int depth) {
	    
	//base case
        if (start > end) {
		return nullptr;
	}
	
	//make middle element into the root
	int middle = (start + end) / 2;

	//BSTNode<Data>* n = new BSTNode<Data> (data[middle]);
	
	BSTNode<Data>* n;

	//root = new BSTNode<Data> (data[middle]);

	n->data = data[middle];

	n->left = buildSubtree(data, start, middle -1, ++depth);
	n->right = buildSubtree(data, middle + 1, end, ++depth);

	return n;
    }

    // Add more helper functions below
    /** Recursive height helper function
     * This function will compute the  depth of the BST,
     * that is, the number of nodes along the path from the root node, 
     * down to the farthest leaf node.
     */
    int heightHelper(BSTNode<Data>* n) const {
	    //if empty BST, return -1
	    if (n == 0) return -1;
	    
	    //compute the depth of each subtree
	    int right = heightHelper(n->right);
	    int left = heightHelper(n->left);
		
	    // return the larger depth calculated
	    if (left < right){
		    return (right+1);
	    }
	    else{ 
		    return (left+1);
	    }
    }

    //Recursive inroder traversal helper function 
    vector<Data> inorder(BSTNode<Data>* n)  {
	    //vector<Data> v1;

	    if (n == 0) {
		    return v1;
	    }
	    //traverse the left subtree
	    inorder(n->left);
	    //add current node to vector
	    v1.push_back(n->data);
	    //traverse the right subtree
	    inorder(n->right);

	    return v1;
    }

  /**  bool deleteNode(BSTNode<Data>* n, const Data& item){
	    //base case: empty bst
	    if ( n == 0 ) return 0;
	    
	    //find if Node to be deleted is in BST
	    while (n) {
		    if (item < n->data){
			    n = n->left;
		    }
		    else if (n->data < item){
			    n = n->right;
		    }
		    //found it!!
		    else { 
			    //CASE 1: node to be deleted has no children
			    //** it is a leaf node
			    if (n->left == 0 && n->right == 0) {
				    if ( n != root ){
					    //either it is a left child or right child
					    if ( (n->parent)->left == n )
						    (n->parent)->left = nullptr;
					    else
						    (n->parent)->right = nullptr;
				    }

				    //if BST only has one  node, the root, delete it
				    else
					    root = nullptr;

				    delete n; //free it!
				    --isize; //update size
			    }

			    //CASE 2:  node to be deleted has two  children
			    else if (n->left && n->right) {

				    //find it's successor node
				    BSTNode<Data>* succ = minKey(n->right);

				    //store the successor value
				    Data temp = succ->data;

				    //recursively delete the successor
				    deleteNode(root, succ->data);

				    //copy the value of successor to the current node
				    n->data = temp;
			    }

			    //CASE 3: node to be deleted has only one child
			    else {	

				    //find the child node
				    BSTNode<Data>* child = (n->left)? n->left: n->right;
	
				    //if node to be deleted is not a root node
				    //then set it's parent to it's child
				    if (n != root) {
					    if (n == (n->parent)->left)
						    (n->parent)->left = child;
					    else
						    (n->parent)->right = child;
				    }

				    //if node to be deleted is root node, then set root to child
				    else
					    root = child;

				    delete n;
				    --isize;
			    }

			    return 1;

		    }
	    }
	    return 0;
    }*/

    //helper function for deleteNode
    //this function finds the minimum value node in a subtree rooted at curr
    BSTNode<Data>* minKey(BSTNode<Data>* curr){
	    while(curr->left != 0) {
		    curr = curr->left;
	    }
	    return curr;
    }
};

#endif  // BST_HPP
