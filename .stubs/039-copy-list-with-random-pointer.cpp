/*
39. Copy List with Random Pointer  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/copy-list-with-random-pointer/

You get the head of a linked list of n nodes. Besides `next`, every node has a
`random` pointer that points to any node of the same list (possibly itself) or
is nullptr. Return the head of a deep copy of the list:

  * the copy consists of exactly n brand-new nodes,
  * copy node i has the same val as original node i,
  * the next and random pointers of the copies point to copies, so that the
    copy has the same shape as the original. No pointer in the copy may point
    to a node of the original list.

When you return, the original list must be exactly as it was (you may change
it temporarily). Return nullptr for an empty list.

Node (an alias of RandomNode) has `int val`, `Node* next`, `Node* random`, and
a constructor Node(int val) that sets both pointers to nullptr.

In the examples a list is written as [val, random_index] per node, where
random_index is the 0-based position of the node `random` points to, or null.

Example 1:
    Input:  head = [[3, null], [5, 0], [9, 3], [1, 1]]
    Output: [[3, null], [5, 0], [9, 3], [1, 1]]
            (node 2's random points forward to node 3, node 3's back to node 1)

Example 2:
    Input:  head = [[4, 0]]
    Output: [[4, 0]]       (the single node's random points to itself)

Example 3:
    Input:  head = []
    Output: []

Constraints:
    0 <= n <= 1000
    -10^4 <= Node.val <= 10^4
    Node.random is nullptr or points to a node of the list

Target: O(n) time. Follow-up: O(1) extra space besides the copy itself.
*/
#include "prelude.hpp"

using Node = RandomNode;

class Solution {
public:
    Node* copyRandomList(Node* head) {
        throw NotImplemented();
    }
};
