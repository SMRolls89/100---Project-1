/**
 * Steffe Reyes (A16083679)
 * Ji Hyun An (A91108783)
 * CSE100 - PA1
 * */
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"

using namespace std;

/**
 * This file contains the methods and 
 * class definition for a BSTIterator
 */
template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /**
     * Constructor that initialize the current BSTNode
     * in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->getData(); }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /** Equality test operator */
    bool operator==(BSTIterator<Data> const& other) const {
	    /** Return true if the reference, other, is equal to the calling object. 
	     *  Two iterators are equal if they ar eboth pointing to the same BSTNode.
	     */
	    if(curr == other.curr)
		   return true;
	    else
		   return false;
    }

    /** Inequality test operator */
    bool operator!=(BSTIterator<Data> const& other) const {
	    // Return true if other is not equal to the calling object
	    if(curr != other.curr)
		    return true;
	    else
		    return false;
    }
};

#endif  // BSTITERATOR_HPP
