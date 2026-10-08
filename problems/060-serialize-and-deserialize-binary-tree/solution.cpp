/*
60. Serialize and Deserialize Binary Tree  ·  Hard  ·  Trees
Source: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

Design a class Codec that turns a binary tree into a string and back:

    string serialize(TreeNode* root)     encodes the tree (nullptr = empty tree) as a string
    TreeNode* deserialize(string data)   rebuilds the tree from such a string

The format is entirely up to you; the only requirement is the round trip:
deserialize(serialize(root)) must give a tree with exactly the same shape and
values as root. The tests use one Codec object to serialize and a different one
to deserialize (so don't keep the tree in the object, and don't use static or
global state), and deserialize must build new nodes.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). TreeNode has
int val and TreeNode* left, right.

Example 1:
    Input:  root = [7, -3, 12, null, 5, 100]
    Output: [7, -3, 12, null, 5, 100]
            (Codec ser, deser;  deser.deserialize(ser.serialize(root)) rebuilds
             the same tree; the string in between can be anything you like)

Example 2:
    Input:  root = []
    Output: []

Constraints:
    0 <= number of nodes <= 10^4
    -1000 <= Node.val <= 1000

Target: O(n) time for both directions.
*/
#include "prelude.hpp"

class Codec {
public:
    string serialize(TreeNode* root) {
        throw NotImplemented();
    }

    TreeNode* deserialize(string data) {
        throw NotImplemented();
    }
};
