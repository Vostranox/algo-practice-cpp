/*
191. Binary Search Tree Iterator  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/binary-search-tree-iterator/

Implement an iterator that walks through the values of a binary search tree
(every value in a node's left subtree is smaller than the node's value, every
value in its right subtree is larger) in increasing order, i.e. in inorder.

    BSTIterator(root)   starts an iteration over the tree rooted at root,
                        positioned before the smallest value
    next() -> int       moves to the next value and returns it
    hasNext() -> bool   true if there is still a value after the current position

next is only called when there is a next value. hasNext doesn't move the
iterator, so calling it repeatedly gives the same answer.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). TreeNode has
int val and TreeNode* left, right.

Example:
    BSTIterator([8, 4, 10, null, 6, null, 12])
    next()    -> 4
    next()    -> 6
    hasNext() -> true
    next()    -> 8
    next()    -> 10
    next()    -> 12
    hasNext() -> false

Constraints:
    1 <= number of nodes <= 10^5
    0 <= Node.val <= 10^6
    at most 10^5 calls to next and hasNext in total

Target: next and hasNext in O(1) amortized time; the tests make up to 10^5
calls on trees with 10^5 nodes.
Follow-up: use only O(h) memory, where h is the height of the tree.
*/
#include "prelude.hpp"

class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
    }

    int next() {
        throw NotImplemented();
    }

    bool hasNext() {
        throw NotImplemented();
    }
};
