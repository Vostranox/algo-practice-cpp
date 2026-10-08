/*
45. Reverse Nodes in k-Group  ·  Hard  ·  Linked List
Source: https://leetcode.com/problems/reverse-nodes-in-k-group/

You get the head of a singly linked list and a positive integer k. Cut the list
into consecutive groups of k nodes, starting from the head, and reverse the
order of the nodes inside every complete group. If the length isn't a multiple
of k, the leftover nodes at the end (fewer than k) keep their original order.
Return the head of the resulting list.

You may not change the values stored in the nodes; only the next pointers may
change (the nodes themselves stay the same objects).

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [4, 8, 15, 16, 23, 42, 7, 11], k = 3
    Output: [15, 8, 4, 42, 23, 16, 7, 11]   (7, 11 are leftovers and keep their order)

Example 2:
    Input:  head = [3, 1, 2, 5], k = 2
    Output: [1, 3, 5, 2]

Example 3:
    Input:  head = [9, 6, 3], k = 1
    Output: [9, 6, 3]

Constraints:
    1 <= k <= n <= 5000   (n = number of nodes)
    0 <= Node.val <= 1000

Target: O(n) time. Follow-up: O(1) extra memory.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        throw NotImplemented();
    }
};
