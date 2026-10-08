/*
183. Rotate List  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/rotate-list/

You get the head of a singly linked list and an integer k >= 0. Rotate the list
to the right k times, where one rotation detaches the last node and puts it in
front of the head. Return the head of the rotated list. Note that k can be far
larger than the length of the list.

You may not change the values stored in the nodes; only the next pointers may
change (the nodes themselves stay the same objects).

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [10, 20, 30, 40, 50], k = 2
    Output: [40, 50, 10, 20, 30]

Example 2:
    Input:  head = [8, -1, 6], k = 7
    Output: [6, 8, -1]         (3 rotations restore the list, so 7 act like 1)

Example 3:
    Input:  head = [], k = 5
    Output: []

Constraints:
    0 <= number of nodes <= 500
    -100 <= Node.val <= 100
    0 <= k <= 2 * 10^9

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        throw NotImplemented();
    }
};
