#include "prelude.hpp"

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return nullptr;
        int n = 1;
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            ++n;
        }
        int steps = n - k % n;
        tail->next = head;
        ListNode* new_tail = tail;
        for (int i = 0; i < steps; ++i) {
            new_tail = new_tail->next;
        }
        ListNode* new_head = new_tail->next;
        new_tail->next = nullptr;
        return new_head;
    }
};
