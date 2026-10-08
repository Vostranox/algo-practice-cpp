#include "prelude.hpp"

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* group_prev = &dummy;
        while (true) {
            ListNode* kth = group_prev;
            for (int i = 0; i < k && kth; ++i) {
                kth = kth->next;
            }
            if (!kth) return dummy.next;
            ListNode* group_next = kth->next;
            ListNode* prev = group_next;
            ListNode* cur = group_prev->next;
            while (cur != group_next) {
                ListNode* next = cur->next;
                cur->next = prev;
                prev = cur;
                cur = next;
            }
            ListNode* first = group_prev->next;
            group_prev->next = kth;
            group_prev = first;
        }
    }
};
