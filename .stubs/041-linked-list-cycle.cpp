/*
41. Linked List Cycle  ·  Easy  ·  Linked List
Source: https://leetcode.com/problems/linked-list-cycle/

You get the head of a singly linked list. Return true if the list contains a
cycle, i.e. following next pointers from the head eventually reaches a node
that was already visited; return false if the walk ends at nullptr.

Don't modify the list.

ListNode has `int val` and `ListNode* next`.
In the examples, `pos` is the 0-based index of the node that the last node's
next points back to (-1 = no cycle). pos is only used to build the input; your
function does not receive it.

Example 1:
    Input:  head = [4, 1, 7, 2], pos = 1
    Output: true           (2 -> back to 1)

Example 2:
    Input:  head = [6, 3], pos = 0
    Output: true

Example 3:
    Input:  head = [9], pos = -1
    Output: false

Constraints:
    0 <= number of nodes <= 10^4
    -10^5 <= Node.val <= 10^5
    pos is -1 or a valid index in the list

Target: O(n) time.
Follow-up: can you do it with O(1) extra memory?
*/
#include "prelude.hpp"

class Solution {
public:
    bool hasCycle(ListNode* head) {
        throw NotImplemented();
    }
};
