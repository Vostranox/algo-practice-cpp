/*
38. Remove Nth Node From End of List  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/remove-nth-node-from-end-of-list/

You get the head of a singly linked list and an integer n. Remove the n-th node
counting from the end of the list (n = 1 is the last node, n = length is the
first) and return the head of the resulting list (nullptr if it is now empty).

Remove the node by unlinking it: the remaining nodes must be the original node
objects, in their original order, with their values unchanged. (You don't
need to delete the removed node.)

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [4, 7, 1, 9, 3], n = 2
    Output: [4, 7, 1, 3]       (9 is second from the end)

Example 2:
    Input:  head = [5, 8], n = 2
    Output: [8]                (the head itself is removed)

Example 3:
    Input:  head = [6], n = 1
    Output: []

Constraints:
    1 <= number of nodes <= 30
    0 <= Node.val <= 100
    1 <= n <= number of nodes

Follow-up: can you do it in a single pass over the list?
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        throw NotImplemented();
    }
};
