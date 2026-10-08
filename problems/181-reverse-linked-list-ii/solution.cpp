/*
181. Reverse Linked List II  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/reverse-linked-list-ii/

You get the head of a singly linked list and two positions left <= right,
counted from 1 at the head. Reverse the order of the nodes at positions left
through right (inclusive); the nodes before and after that stretch stay where
they are. Return the head of the resulting list.

You may not change the values stored in the nodes; only the next pointers may
change (the nodes themselves stay the same objects).

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [10, 20, 30, 40, 50, 60], left = 2, right = 5
    Output: [10, 50, 40, 30, 20, 60]

Example 2:
    Input:  head = [7, 3, 9], left = 1, right = 3
    Output: [9, 3, 7]          (the whole list, so the head changes)

Example 3:
    Input:  head = [4, 8], left = 2, right = 2
    Output: [4, 8]             (a stretch of one node: nothing moves)

Constraints:
    1 <= n <= 500   (n = number of nodes)
    -500 <= Node.val <= 500
    1 <= left <= right <= n

Target: O(n) time, O(1) extra space. Follow-up: do it in a single pass.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        throw NotImplemented();
    }
};
