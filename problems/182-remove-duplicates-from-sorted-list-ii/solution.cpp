/*
182. Remove Duplicates from Sorted List II  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

You get the head of a linked list whose values are sorted in non-decreasing
order. Every value that occurs more than once must disappear completely: remove
all nodes carrying it, not just the extra copies. Return the head of what is
left (still sorted), or nullptr if nothing is left.

Remove nodes by unlinking them: the returned list must be made of the original
node objects that survive, in their original order, with their values
unchanged. (Whether you delete the removed nodes is up to you.)

ListNode has `int val` and `ListNode* next` (nullptr after the last node).
In the examples a list is written as the array of its values, front to back.

Example 1:
    Input:  head = [2, 5, 5, 6, 8, 8, 8, 9]
    Output: [2, 6, 9]

Example 2:
    Input:  head = [3, 3, 3, 4, 7]
    Output: [4, 7]             (the head goes, too)

Example 3:
    Input:  head = [6, 6]
    Output: []

Constraints:
    0 <= number of nodes <= 300
    -100 <= Node.val <= 100
    the values are sorted in non-decreasing order

Target: O(n) time, O(1) extra space.
*/
#include "prelude.hpp"

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        throw NotImplemented();
    }
};
