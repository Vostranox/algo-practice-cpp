/*
203. Sort List  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/sort-list/

You get the head of a singly linked list. Sort the list into non-decreasing
order of val and return the head of the sorted list.

Sort by re-linking the nodes: the returned list must contain exactly the
original node objects, each still holding its original val. (Copying the values
into an array, sorting that and writing the values back is not allowed.) Nodes
with equal values may end up in any order among themselves.

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [4, -2, 9, 0]
    Output: [-2, 0, 4, 9]

Example 2:
    Input:  head = [3, 1, 3, 2, 1]
    Output: [1, 1, 2, 3, 3]

Example 3:
    Input:  head = []
    Output: []

Constraints:
    0 <= number of nodes <= 5 * 10^4
    -10^5 <= Node.val <= 10^5

Target: O(n log n) time; merge sort suits linked lists. (The large test sorts
several random 5 * 10^4-node lists, so an O(n^2) insertion sort times out.)
Follow-up: O(1) extra memory (bottom-up merge sort, no recursion).
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        throw NotImplemented();
    }
};
