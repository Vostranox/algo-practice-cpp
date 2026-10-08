/*
187. Populating Next Right Pointers in Each Node II  ·  Medium  ·  Trees
Source: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

Every node of this binary tree has, besides its two children, a pointer
`next`, which is nullptr in all nodes when you get the tree. Set each node's
next to the node directly to its right on the same level, i.e. the next node
of that level in left-to-right order, even when it hangs under a different
parent. The rightmost node of each level keeps next == nullptr. Leave left,
right and val unchanged, and return root.

The tree can have any shape: a node may have 0, 1 or 2 children, so
neighbours on a level can be far apart.

The node type Node (an alias of NextNode from prelude.hpp) has int val and
Node* left, right, next.

Trees are written in level-order form: nodes level by level, left to
right, with null for a missing child (trailing nulls omitted). The output is
shown as each level's values, read by following next pointers from the
level's leftmost node, then # to mark where next is nullptr.

Example 1:
    Input:  root = [6, 3, 9, null, 4, 8, null, 1, null, null, 5]
    Output: [6, #, 3, 9, #, 4, 8, #, 1, 5, #]
            (4 and 8 have different parents; so do 1 and 5)

Example 2:
    Input:  root = [10, 20, 30, 40, 50, null, 60, 70, null, null, null, null, 80]
    Output: [10, #, 20, 30, #, 40, 50, 60, #, 70, 80, #]
            (70's next is 80, skipping 40's missing right child, the childless
             50 and 60's missing left child)

Example 3:
    Input:  root = []
    Output: []

Constraints:
    0 <= number of nodes <= 6000
    -100 <= Node.val <= 100

Target: O(n) time.
Follow-up: use only O(1) extra space (the recursion stack doesn't count) —
no queue holding a whole level.
*/
#include "prelude.hpp"

using Node = NextNode;

class Solution {
public:
    Node* connect(Node* root) {
        throw NotImplemented();
    }
};
