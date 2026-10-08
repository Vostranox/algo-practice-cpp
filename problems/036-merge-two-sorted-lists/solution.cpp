/*
36. Merge Two Sorted Lists  ·  Easy  ·  Linked List
Source: https://leetcode.com/problems/merge-two-sorted-lists/

You get the heads of two singly linked lists, list1 and list2, each sorted in
non-decreasing order. Merge them into a single list sorted in non-decreasing
order and return its head (nullptr if both are empty).

Build the result by splicing together the nodes you were given: every node of
both inputs must appear in the result exactly once, with its value unchanged.
Don't allocate new nodes.

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  list1 = [2, 5, 9], list2 = [1, 5, 6, 10]
    Output: [1, 2, 5, 5, 6, 9, 10]

Example 2:
    Input:  list1 = [], list2 = [4]
    Output: [4]

Example 3:
    Input:  list1 = [], list2 = []
    Output: []

Constraints:
    0 <= number of nodes in each list <= 50
    -100 <= Node.val <= 100
    list1 and list2 are both sorted in non-decreasing order

Target: O(n + m) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        throw NotImplemented();
    }
};
