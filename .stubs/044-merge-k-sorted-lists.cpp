/*
44. Merge K Sorted Lists  ·  Hard  ·  Linked List
Source: https://leetcode.com/problems/merge-k-sorted-lists/

You get an array of k singly linked lists, each sorted in ascending
(non-decreasing) order. Merge all of them into one sorted list and return its
head. Return nullptr if there are no lists or all of them are empty.

Build the result by splicing together the nodes you were given: every input
node must appear in the result exactly once, with its value unchanged. Don't
allocate new nodes.

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  lists = [[2, 6, 9], [1, 6], [3, 4, 10]]
    Output: [1, 2, 3, 4, 6, 6, 9, 10]

Example 2:
    Input:  lists = []
    Output: []

Example 3:
    Input:  lists = [[], [5]]
    Output: [5]

Constraints:
    0 <= k <= 10^4
    0 <= length of each list <= 500
    -10^4 <= Node.val <= 10^4
    each list is sorted in ascending order
    the total number of nodes N is at most 10^4

Target: O(N log k) time.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        throw NotImplemented();
    }
};
