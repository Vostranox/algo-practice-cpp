#include "prelude.hpp"

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode less_head, rest_head;
        ListNode *less = &less_head, *rest = &rest_head;
        for (; head; head = head->next) {
            if (head->val < x) {
                less = less->next = head;
            } else {
                rest = rest->next = head;
            }
        }
        rest->next = nullptr;
        less->next = rest_head.next;
        return less_head.next;
    }
};
