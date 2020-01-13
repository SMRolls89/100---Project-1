/**
 * Steffe Reyes (A16083679)
 * Ji Hyun An (A91108783)
 * */
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"

using namespace std;

/**
 * TODO: add class header
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

    /** equality test */
    bool operator==(BSTIterator<Data> const& other) const {
	    if(curr = other.curr)
		   return true;
	    else
		   return false;
    }

    /** inequality test */
    bool operator!=(BSTIterator<Data> const& other) const {
	    if(curr != other.curr)
		    return true;
	    else
		    return false;
    }
};

#endif  // BSTITERATOR_HPP
