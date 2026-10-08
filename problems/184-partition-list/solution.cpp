/*
184. Partition List  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/partition-list/

You get the head of a singly linked list and a value x. Rearrange the list so
that every node with val < x comes before every node with val >= x. Within each
of the two groups the nodes must keep the relative order they had in the
original list. Return the head of the rearranged list.

You may not change the values stored in the nodes; only the next pointers may
change (the nodes themselves stay the same objects).

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [5, 1, 8, 3, 6, 2], x = 4
    Output: [1, 3, 2, 5, 8, 6]

Example 2:
    Input:  head = [3, 1], x = 2
    Output: [1, 3]

Example 3:
    Input:  head = [4, 7, 4], x = 4
    Output: [4, 7, 4]          (no value is below 4, so nothing moves)

Constraints:
    0 <= number of nodes <= 200
    -100 <= Node.val <= 100
    -200 <= x <= 200

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        throw NotImplemented();
    }
};
