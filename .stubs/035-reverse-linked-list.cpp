/*
35. Reverse Linked List  ·  Easy  ·  Linked List
Source: https://leetcode.com/problems/reverse-linked-list/

You are given the head of a singly linked list. Reverse the list and return
the head of the reversed list (nullptr if the list is empty).

Reverse it by re-linking the nodes you were given: the returned list must be
made of the original node objects. Don't allocate new nodes or overwrite val.

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [3, 8, -1, 6]
    Output: [6, -1, 8, 3]

Example 2:
    Input:  head = [7, 2]
    Output: [2, 7]

Example 3:
    Input:  head = []
    Output: []

Constraints:
    0 <= number of nodes <= 5000
    -5000 <= Node.val <= 5000

Target: O(n) time, O(1) extra space.
Follow-up: write it both iteratively and recursively.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        throw NotImplemented();
    }
};
