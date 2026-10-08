/*
37. Reorder List  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/reorder-list/

You get the head of a singly linked list with n nodes L0 -> L1 -> ... -> L(n-1).
Rearrange it to alternate between the front and the back:

    L0 -> L(n-1) -> L1 -> L(n-2) -> L2 -> L(n-3) -> ...

Work in place and return nothing: the list is checked starting from the head
you were given. You may not change the values stored in the nodes; only the
next pointers may change (the nodes themselves stay the same objects).

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [10, 20, 30, 40]
    Output: [10, 40, 20, 30]

Example 2:
    Input:  head = [5, 9, 2, 7, 4]
    Output: [5, 4, 9, 7, 2]

Example 3:
    Input:  head = [8]
    Output: [8]

Constraints:
    1 <= number of nodes <= 5 * 10^4
    1 <= Node.val <= 1000

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    void reorderList(ListNode* head) {
        throw NotImplemented();
    }
};
