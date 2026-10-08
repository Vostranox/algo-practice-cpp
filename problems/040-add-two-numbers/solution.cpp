/*
40. Add Two Numbers  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/add-two-numbers/

Two non-empty linked lists each hold a non-negative integer, one decimal digit
per node, with the digits in reverse order: the head holds the ones digit, the
next node the tens digit, and so on. Return their sum as a new list in the same
format. Neither input has leading zeros, except the number 0 itself (a single
node 0), and the result must not have any either.

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  l1 = [5, 0, 3], l2 = [8, 9]
    Output: [3, 0, 4]          (305 + 98 = 403)

Example 2:
    Input:  l1 = [0], l2 = [0]
    Output: [0]

Example 3:
    Input:  l1 = [9, 9, 9], l2 = [1]
    Output: [0, 0, 0, 1]       (999 + 1 = 1000)

Constraints:
    1 <= number of nodes in each list <= 100
    0 <= Node.val <= 9
    no leading zeros (the most significant digit, i.e. the last node, is not 0
    unless the number is 0)

Target: O(max(n, m)) time.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        throw NotImplemented();
    }
};
