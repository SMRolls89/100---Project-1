#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}


TEST(BSTTests, EMPTY_BST_SIZE_TEST) {
	BST<int> bst;
	ASSERT_EQ(bst.size(), 0);	
}

TEST(BSTTests, EMPTY_BST_EMPTYBOOLFUNC) {
	BST<int> bst;
	ASSERT_EQ(bst.empty(), 1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

// TODO: add more BST tests here

TEST_F(SmallBSTFixture, SMALL_HEIGHT_TEST) {
	ASSERT_EQ(bst.height(), 2 );
}

TEST_F(SmallBSTFixture, SMALL_FIND_TEST) {
	//assert that the element was found in the BST
	ASSERT_EQ(*(bst.find(4)), 4);
}

TEST_F(SmallBSTFixture, SMALL_NOTFOUND_TEST) {
	//asset that the element was not found in the BST
	ASSERT_EQ(bst.find(2), bst.end());
}
TEST_F(SmallBSTFixture, SMALL_EMPTYBOOL_TEST) {
	ASSERT_EQ(bst.empty(), 0);
}

TEST_F(SmallBSTFixture, SMALL_BEGIN_TEST) {
	ASSERT_EQ(*(bst.begin()), -33);
}

TEST_F(SmallBSTFixture, SMALL_ENG_TEST) {
	ASSERT_NE(bst.end(), bst.begin());
}

TEST_F(SmallBSTFixture, SMALL_INSERT_TEST) {
	ASSERT_TRUE(bst.insert(48));

}

//testing for deleteNode 
TEST_F(SmallBSTFixture, SMALL_DELETENODE) {
	ASSERT_EQ(*(bst.find(-33)), -33);
	ASSERT_TRUE(bst.deleteNode(-33));
	ASSERT_EQ(bst.find(-33), nullptr);
}

TEST_F(SmallBSTFixture, SMALL_DELETENODE_RIGHT){
	ASSERT_TRUE(bst.deleteNode(100));
}

TEST_F(SmallBSTFixture, SMALL_DELETENODE_CHILD){
	ASSERT_FALSE(bst.deleteNode(27));
}
//testing for finding something that's not in the tree
/*TEST_F(SmallBSTFixture, SMALL_FIND){
	ASSERT
}*/

TEST_F(SmallBSTFixture, SMALL_inorder) {
	ASSERT_NE(bst.inorder(), bst.inorder());
}

