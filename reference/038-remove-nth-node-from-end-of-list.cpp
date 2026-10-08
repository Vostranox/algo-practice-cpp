#include "prelude.hpp"

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);
        ListNode* left = &dummy;
        ListNode* right = head;
        while (n--) {
            right = right->next;
        }
        while (right) {
            left = left->next;
            right = right->next;
        }
        left->next = left->next->next;
        return dummy.next;
    }
};
