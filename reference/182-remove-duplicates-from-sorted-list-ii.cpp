#include "prelude.hpp"

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy;
        ListNode* tail = &dummy;
        while (head) {
            ListNode* run_end = head;
            while (run_end->next && run_end->next->val == head->val) {
                run_end = run_end->next;
            }
            if (run_end == head) {
                tail = tail->next = head;
            }
            head = run_end->next;
        }
        tail->next = nullptr;
        return dummy.next;
    }
};
